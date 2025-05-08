#ifndef HTML_H
#define HTML_H

const char html[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
  <title>OG Star Tracker Control</title>
  <meta name='viewport' content='width=device-width, initial-scale=1'>
  <style>
    body {
      background-color: black;
      text-align: center;
      color: white; /* Adicionado para garantir que o texto seja visível */
    }
    button {
      background-color: white;
      color: black;
      border: none;
      padding: 15px 32px;
      text-align: center;
      text-decoration: none;
      display: inline-block;
      font-size: 16px;
      margin: 4px 2px;
      cursor: pointer;
    }
    select {
      font-size: 16px;
      padding: 5px;
    }
    input[type='number'] {
      font-size: 16px;
      padding: 5px;
      width: 50%;
    }
    label {
      display: inline-block;
      text-align: left;
      margin: 10px;
      font-size: 20px;
    }
    #main-title {
      color: white;
    }
    #status {
      font-size: 24px;
      margin: 20px;
    }
  </style>
</head>
<body>
  <h1 id="main-title">OG Star Tracker Control</h1>
  <label> Battery Voltage: <span id='status_bat'></span></label><br>
  <label>Sidereal Tracking:</label><br>
  <button onclick=\"sendRequest('/on')\">ON</button>
  <button onclick=\"sendRequest('/off')\">OFF</button><br>
  <label>Slew Control:</label><br>
  <label>Speed:</label>
  <select id='slew-select'>
    <option value='1'>1</option>
    <option value='2'>2</option>
    <option value='3'>3</option>
    <option value='4'>4</option>
    <option value='5'>5</option>
  </select><br>
  <button onclick=\"sendSlewRequest('/left')\">&#8592;</button>
  <button onclick=\"sendSlewRequest('/right')\">&#8594;</button><br>
  <label>Intervalometer Control:</label><br>
  <input type='number' id='exposure' placeholder='Exposure length (s)'>
  <input type='number' id='num-exposures' placeholder='Number of Exposures'><br>
  <button onclick=\"sendCaptureRequest()\">Start capture</button>
  <button onclick=\"sendRequest('/abort')\">Abort capture</button><br>
  <label>STATUS:</label><br>
  <p id='status'></p>
  <script>
    function sendRequest(url) {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
          document.getElementById("status").innerHTML = this.responseText;
        }
      };
      xhttp.open("GET", url, true);
      xhttp.send();
    }

    function sendSlewRequest(url) {
      var speed = document.getElementById('slew-select').value;
      var slewurl = url + '?speed=' + speed;
      sendRequest(slewurl);
    }

    function sendCaptureRequest() {
      var exposure = document.getElementById('exposure').value.trim();
      var numExposures = document.getElementById('num-exposures').value.trim();
      var intervalometerUrl = '/start?exposure=' + exposure + '&numExposures=' + numExposures;
      sendRequest(intervalometerUrl);
    }

    function updateBattery() {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
          document.getElementById("status_bat").innerHTML = this.responseText;
        }
      };
      xhttp.open("GET", "/battery", true);
      xhttp.send();
    }

    // Atualiza o status da bateria a cada 5 segundos
    setInterval(updateBattery, 5000);
  </script>
</body>
</html>
)=====";

#endif
