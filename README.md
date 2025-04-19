# Easy-Management-Organization

A lightweight full-stack employee management system using a **C++ backend with Crow** and a **vanilla JavaScript frontend**.  
This project allows users to manage employee records — including adding, editing, deleting, and filtering.

---

## 📌 Features

### ✅ Add New Employee
- Add employees with `ID`, `Full Name`, `Role`, and `Monthly Salary`
- Prevents duplicate employee IDs

### 🔍 Filter Employees
- Filter by:
  - Employee ID
  - Name
  - Role
  - Min & Max Salary

### 📄 View Employee List
- Dynamic employee table displays:
  - ID
  - Name
  - Role
  - Salary
  - Edit/Delete buttons

### ✏️ Edit / ❌ Delete
- Update employee data or delete records
- Changes are persisted in `employees.json`

### 🌐 CORS Support
- Cross-Origin Resource Sharing enabled to allow seamless communication between frontend and backend

---

## 🧱 Project Structure
payroll-web/ ├── backend/ │ ├── build/ # Build output │ ├── Crow/ # Crow (header-only web framework) │ ├── main.cpp # Backend logic │ ├── Employee.h # Employee model │ └── CMakeLists.txt # Build config ├── frontend/ │ ├── index.html # Main UI │ ├── app.js # JS logic │ └── style.css # Styling


---

## 🛠️ Prerequisites

### Common Dependencies

| Library           | Description                                  | Required |
|------------------|----------------------------------------------|----------|
| **Crow**         | Lightweight C++ web framework (header-only)  | ✅ Yes   |
| **Boost**        | Required by Crow                              | ✅ Yes   |
| **nlohmann/json**| JSON library for C++                          | ✅ Yes   |

---

## 🐧 Linux Installation (Ubuntu/Debian)

### 1. Install System Packages

      sudo apt update
      sudo apt install g++ cmake libboost-all-dev nlohmann-json3-dev

### 2. Clone Crow (header-only)
      
      cd backend
      git clone https://github.com/CrowCpp/Crow.git
      cd ../
      ./build.sh

## Windows Installation
### 1. Install Tools
CMake
Visual Studio with C++ build tools
Boost
Crow (clone manually)
nlohmann/json

### 💡 You can also use vcpkg:

      vcpkg install boost
      vcpkg install nlohmann-json

### 2. Build Backend and run backend

      .\bash.bat

## 🌐 Frontend Usage
No installation needed.
Just open frontend/index.html in your browser.
Ensure backend is running on: http://localhost:18080

## 📷 Screenshots
### 💻 UI (Add/Edit/Delete Employee)


## 🧾 Notes
The backend uses a employees.json file to store data persistently.
CORS headers are enabled to allow frontend requests.
Port: 18080 (you can change this in main.cpp if needed)

## 🔮 Future Ideas
Integrate with an actual database (MySQL, SQLite)
Export/Import CSV support
Authentication system
Salary analytics dashboard

## 📬 Author
Built with ❤️ using C++ & JavaScript.
