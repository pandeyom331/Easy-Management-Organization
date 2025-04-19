#pragma once
#include <string>
#include <nlohmann/json.hpp>

struct Employee {
    int id;
    std::string name;
    std::string role;
    double salary;

    nlohmann::json to_json() const {
        return nlohmann::json{
            {"id", id},
            {"name", name},
            {"role", role},
            {"salary", salary}
        };
    }

    static Employee from_json(const nlohmann::json& j) {
        return Employee{
            j.at("id").get<int>(),
            j.at("name").get<std::string>(),
            j.at("role").get<std::string>(),
            j.at("salary").get<double>()
        };
    }
};