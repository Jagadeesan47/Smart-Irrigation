#pragma once

#include <SIS.h>

// HTML content
const char htmlPage[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Wireless Control Dashboard</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            background-color: #f0f0f0;
            margin: 0;
            padding: 0;
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
            overflow: hidden;
        }
        .container {
            background: white;
            border-radius: 10px;
            box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1);
            width: 90%;
            max-width: 500px;
            padding: 20px;
            display: flex;
            flex-direction: column;
            align-items: center;
        }
        .header {
            text-align: center;
            width: 100%;
            padding-bottom: 20px;
        }
        .content-wrapper {
            display: flex;
            flex-direction: column;
            width: 100%;
        }
        .sidebar {
            display: flex;
            flex-direction: column;
            align-items: center;
            width: 100%;
            margin-bottom: 20px;
        }
        .menu {
            display: flex;
            flex-direction: row;
            justify-content: space-between;
            align-items: center;
            width: 100%;
        }
        .menu button {
            padding: 10px 20px;
            font-size: 16px;
            cursor: pointer;
            border: none;
            border-radius: 10px;
            background-color: #007bff;
            color: white;
            margin-bottom: 10px;
            transition: background-color 0.3s;
            width: 30%;
        }
        .menu button:hover {
            background-color: #0056b3;
        }
        .content {
            display: flex;
            flex-direction: column;
            align-items: center;
            width: 100%;
        }
        .section {
            display: none;
            width: 100%;
        }
        .section.active {
            display: block;
        }
        .control-panel {
            display: flex;
            flex-direction: column;
            align-items: center;
            width: 100%;
        }
        .control-group {
            width: 100%;
            display: flex;
            flex-direction: column;
            align-items: center;
            padding: 10px;
            border: 2px solid #ddd;
            border-radius: 15px;
            margin-bottom: 20px;
            background-color: #f9f9f9;
        }
        .control-group div {
            width: 100%;
            text-align: center;
            margin-bottom: 10px;
        }
        .toggle-switch {
            position: relative;
            width: 60px;
            height: 30px;
            display: inline-block;
        }
        .toggle-switch input {
            display: none;
        }
        .slider {
            position: absolute;
            cursor: pointer;
            top: 0;
            left: 0;
            right: 0;
            bottom: 0;
            background-color: red;
            transition: 0.4s;
            border-radius: 15px;
        }
        .slider:before {
            position: absolute;
            content: "OFF";
            height: 24px;
            width: 30px;
            border-radius: 50%;
            left: 3px;
            bottom: 3px;
            background-color: white;
            transition: 0.4s;
            text-align: center;
            line-height: 24px;
            color: red;
            font-weight: bold;
        }
        input:checked + .slider {
            background-color: #28a745;
        }
        input:checked + .slider:before {
            transform: translateX(30px);
            content: "ON";
            color: #28a745;
        }
        .status-text {
            font-weight: bold;
            color: #555;
        }
        .footer {
            text-align: center;
            padding-top: 20px;
            font-size: 14px;
            color: #777;
            width: 100%;
        }
    </style>
</head>
<body onload="fetchInitialState()">
    <div class="container">
        <header class="header">
            
            <h2 style='color:#2c3e50; border-bottom:2px solid #2c3e50; padding-bottom:5px; text-align:center;'>Controlling System</h2>
        </header>
        <div class="content-wrapper">
            
            <div class="content">
                <main>
                    <section id="home" class="section active control-panel">
                        <div class="control-group">
                            <div>Motor Pump 1</div>
                            <div id="status-1" class="status-text">Status: OFF</div>
                            <label class="toggle-switch">
                                <input type="checkbox" id="relay1" onchange="toggleCheckbox(this, 1)">
                                <span class="slider"></span>
                            </label>
                        </div>
                    </section>
                    <section id="settings" class="section">
                        <h2>Terms and Conditions</h2>
                        <p>Here are the terms and conditions...</p>
                    </section>
                    <section id="about" class="section">
                        <h2>About Us</h2>
                        <p>Information about the company...</p>
                    </section>
                </main>
                <footer class="footer">
                    <p>&copy; 2025 IncepicX JM EduTech Services (OPC) Pvt Ltd.</p>
                </footer>
            </div>
        </div>
    </div>
    <script>
        function showSection(sectionId) {
            const sections = document.querySelectorAll('.section');
            sections.forEach(section => {
                section.classList.remove('active');
                if (section.id === sectionId) {
                    section.classList.add('active');
                }
            });
        }

        function toggleCheckbox(element, relayNumber) {
            const statusElement = document.getElementById(`status-${relayNumber}`);
            if (element.checked) {
                statusElement.textContent = 'Status: ON';
                fetch(`/relay${relayNumber}?state=1`);
            } else {
                statusElement.textContent = 'Status: OFF';
                fetch(`/relay${relayNumber}?state=0`);
            }
        }

        function fetchInitialState() {
            fetch('/relay1_state')
                .then(response => response.text())
                .then(state => {
                    const relay1 = document.getElementById('relay1');
                    const status1 = document.getElementById('status-1');
                    if (state === '1') {
                        relay1.checked = true;
                        status1.textContent = 'Status: ON';
                    } else {
                        relay1.checked = false;
                        status1.textContent = 'Status: OFF';
                    }
                });
        }
    </script>
</body>
</html>
</div>
)rawliteral";