// === Send Index ===
String getIndex(String ip, int r, int g, int b) {

  // Return Index HTML Page
  // In this Page will fetch to /r/ , /g/, /b/ API with GET parameter <range> {0, 255}

  /* ========================
    You can use your own HTML page that make GET request to ESP32 IP. To check the funtionality go to ESP32 IP page and search /r/?range=100. http://{IP}/r/?range=100
    You will see that the led becomes red.
  ========================= */

  // Convert int to String
  String red = String(r);
  String green = String(g);
  String blue = String(b);

  return R"""(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>RGB Remote Control - ZLL</title>
    <style>
        body {
            display: flex;
            flex-direction: column;
            align-items: center;
            justify-content: center;
            height: 100vh;
            margin: 0;
        }
        input {
            margin: 10px;
        }
    </style>
</head>
<body>
    <!-- Range input from 0 to 255 -->
    <input type="range" min="0" max="255" value=")""" + red + R"""(" id="red">
    <input type="range" min="0" max="255" value=")""" + green + R"""(" id="green">
    <input type="range" min="0" max="255" value=")""" + blue + R"""(" id="blue">

    <script>
        // Get the range inputs
        const red = document.getElementById('red');
        const green = document.getElementById('green');
        const blue = document.getElementById('blue');

        let arr = [red, green, blue];
        let arr_name = ['r', 'g', 'b'];

        let ip = ')""" + ip + R"""(';

        // When any range move send GET request to IP
        function updateBG() {
            document.body.style.backgroundColor = `rgb(${red.value}, ${green.value}, ${blue.value})`;
        }

        for (let i = 0; i < arr.length; i++) {
            arr[i].addEventListener('input', () => {
                fetch(`http://${ip}/${arr_name[i]}/?range=${arr[i].value}`);
                updateBG();
            });
        }


        // Set color
        updateBG();
    </script>
</body>
</html>
  )""";
}

// === 404 Page ===
void notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}