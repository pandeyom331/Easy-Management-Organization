#include "crow_all.h"
#include "Employee.h"
#include <fstream>
#include <vector>
#include <nlohmann/json.hpp>
#include <mutex>
#include <algorithm>
#include <string>

using json = nlohmann::json;
using namespace std;

std::vector<Employee> employees;
std::mutex data_mutex;

struct CORS {
    struct context {};

    void before_handle(crow::request&, crow::response& res, context&) {
        /*res.add_header("Access-Control-Allow-Origin", "*");
        res.add_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
        res.add_header("Access-Control-Allow-Headers", "Content-Type");*/
    }

    void after_handle(crow::request&, crow::response& res, context&) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");
    }
};

std::vector<Employee> loadEmployees() {
    std::ifstream in("employees.json");
    if (!in) return {};

    json j;
    in >> j;

    std::vector<Employee> loaded;
    for (const auto& item : j["employees"]) {
        loaded.push_back(Employee::from_json(item));
    }
    return loaded;
}

void saveEmployees(const std::vector<Employee>& employees) {
    std::ofstream file("employees.json");
    json j;
    j["employees"] = json::array();
    for (const auto& emp : employees) {
        j["employees"].push_back(emp.to_json());
    }
    file << j.dump(4);
}

int main() {
    crow::App<CORS> app;
    employees = loadEmployees();

    CROW_ROUTE(app, "/employees").methods("GET"_method)([](const crow::request& req) {
        auto query_params = crow::query_string(req.url_params);
        std::string search = query_params.get("search") ? query_params.get("search") : "";

        json j = json::array();
        std::lock_guard<std::mutex> lock(data_mutex);
        for (const auto& emp : employees) {
            if (search.empty() || emp.name.find(search) != std::string::npos || emp.role.find(search) != std::string::npos)
                j.push_back(emp.to_json());
        }
        return crow::response(j.dump());
    });

    CROW_ROUTE(app, "/employee").methods("POST"_method)([](const crow::request& req) {
        auto j = json::parse(req.body);
        Employee emp = Employee::from_json(j);
        std::lock_guard<std::mutex> lock(data_mutex);
        
        auto it = std::find_if(employees.begin(), employees.end(), [&emp](const Employee &e){
        	return e.id == emp.id;
	});
	
	if(it!=employees.end()){
		return crow::response(400, "Employee ID already exists.");
	} 
        
        employees.push_back(emp);
        saveEmployees(employees);
        return crow::response(200);
    });

    CROW_ROUTE(app, "/employee/<int>").methods("PUT"_method)([](const crow::request& req, crow::response& res, int id) {
        auto body = json::parse(req.body);
        std::lock_guard<std::mutex> lock(data_mutex);

        auto it = std::find_if(employees.begin(), employees.end(), [id](const Employee& e) {
            return e.id == id;
        });

        if (it != employees.end()) {
            it->name = body["name"];
            it->role = body["role"];
            it->salary = body["salary"];
            saveEmployees(employees);
            res.code = 200;
        } else {
            res.code = 404;
            res.body = "Employee not found";
        }
        res.end();
    });

    CROW_ROUTE(app, "/employee/<int>").methods("DELETE"_method)([](int id) {
        std::lock_guard<std::mutex> lock(data_mutex);
        auto it = std::find_if(employees.begin(), employees.end(), [id](const Employee& e) {
            return e.id == id;
        });

        if (it == employees.end()) {
            return crow::response(404, "Employee not found");
        }

        employees.erase(it);
        saveEmployees(employees);
        return crow::response(200, "Employee deleted");
    });

    CROW_ROUTE(app, "/employees").methods("OPTIONS"_method)([](const crow::request&, crow::response& res) {
        res.code = 204;
        res.end();
    });

    CROW_ROUTE(app, "/employee").methods("OPTIONS"_method)([](const crow::request&, crow::response& res) {
        res.code = 204;
        res.end();
    });

    CROW_ROUTE(app, "/<path>").methods(crow::HTTPMethod::OPTIONS)([](const crow::request& req, crow::response& res, std::string) {
        res.code = 204;
        res.end();
    });

    app.port(18080).multithreaded().run();
}
