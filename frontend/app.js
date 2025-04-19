const API = 'http://localhost:18080';

async function fetchEmployees() {
    const res = await fetch(`${API}/employees`);
    const data = await res.json();
    const table = document.getElementById('employee-table');
    table.innerHTML = '';
    data.forEach(emp => {
        table.innerHTML += `
            <tr>
                <td>${emp.id}</td>
                <td>${emp.name}</td>
                <td>${emp.role}</td>
                <td>${emp.salary}</td>
                <td>
                    <button onclick='deleteEmployee(${emp.id})'>Delete</button>
                </td>
            </tr>
        `;
    });
}

async function addEmployee() {
    const id = +document.getElementById('id').value;
    const name = document.getElementById('name').value;
    const role = document.getElementById('role').value;
    const salary = +document.getElementById('salary').value;

    try {
        const res = await fetch(`${API}/employee`, {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify({ id, name, role, salary })
        });

        if (!res.ok) {
            const errorMsg = await res.text(); // Get error message from backend
            alert(`Failed to add employee: ${errorMsg}`);
        } else {
            closeModal();
            alert("Employee added successfully!");
            fetchEmployees();
            
            document.getElementById('id').value = '';
            document.getElementById('name').value = '';
            document.getElementById('role').value = '';
            document.getElementById('salary').value = '';
        }
    } catch (err) {
        alert("Error connecting to server. Please try again.");
        console.error(err);
    }
}

async function deleteEmployee(id) {
    await fetch(`${API}/employee/${id}`, { method: 'DELETE' });
    fetchEmployees();
}

let allEmployees = [];

async function fetchEmployees() {
    const res = await fetch(`${API}/employees`);
    allEmployees = await res.json();
    renderEmployees(allEmployees);
}

function renderEmployees(list) {
    const table = document.getElementById('employee-table');
    table.innerHTML = '';
    list.forEach(emp => {
        table.innerHTML += `
            <tr id="row-${emp.id}">
                <td>${emp.id}</td>
                <td id="name-${emp.id}">${emp.name}</td>
                <td id="role-${emp.id}">${emp.role}</td>
                <td id="salary-${emp.id}">${emp.salary}</td>
                <td>
                    <button onclick='editEmployee(${emp.id})'>Edit</button>
                    <button onclick='deleteEmployee(${emp.id})'>Delete</button>
                </td>
            </tr>
        `;
    });
}

function editEmployee(id) {
    const name = prompt("Enter new name:", document.getElementById(`name-${id}`).innerText);
    const role = prompt("Enter new role:", document.getElementById(`role-${id}`).innerText);
    const salary = prompt("Enter new salary:", document.getElementById(`salary-${id}`).innerText);

    if (name && role && salary) {
        fetch(`${API}/employee/${id}`, {
            method: 'PUT',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify({ name, role, salary: parseFloat(salary) })
        })
        .then(res => {
            if (res.ok) {
                alert("Employee updated successfully!");
                fetchEmployees();
            } else {
                alert("Failed to update employee.");
            }
        });
    }
    // renderEmployees(allEmployees);
}

function applyFilters() {
    const id = document.getElementById('filter-id').value;
    const name = document.getElementById('filter-name').value.toLowerCase();
    const role = document.getElementById('filter-role').value.toLowerCase();
    const minSalary = parseFloat(document.getElementById('filter-min-salary').value) || 0;
    const maxSalary = parseFloat(document.getElementById('filter-max-salary').value) || Infinity;

    const filtered = allEmployees.filter(emp => {
        const matchesId = !id || emp.id == id;
        const matchesName = emp.name.toLowerCase().includes(name);
        const matchesRole = emp.role.toLowerCase().includes(role);
        const matchesSalary = emp.salary >= minSalary && emp.salary <= maxSalary;

        return matchesId && matchesName && matchesRole && matchesSalary;
    });

    renderEmployees(filtered);
}

function clearFilters() {
    document.getElementById('filter-name').value = '';
    document.getElementById('filter-role').value = '';
    document.getElementById('filter-min-salary').value = '';
    document.getElementById('filter-max-salary').value = '';
    document.getElementById('filter-id').value = '';
    renderEmployees(allEmployees);
}

window.onload = fetchEmployees;


