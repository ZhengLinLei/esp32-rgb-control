<?php
// Get rgb value from database
$data = require('./database/database.php');

try {
    $conn = new PDO("mysql:host=".$data[0].";dbname=".$data[1], $data[2], $data[3]);
    // set the PDO error mode to exception
    $conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
  
    // Get led data 'r', 'g', 'b' from table led
    $sql = "SELECT * FROM led";

    // Prepare and execute the query
    $stmt = $conn->prepare($sql);
    $stmt->execute();

    // Fetch the data from the query
    $result = $stmt->fetch(PDO::FETCH_ASSOC);    
} catch(PDOException $e) {
    $result = ['r' => 0, 'g' => 0, 'b' => 0];
}
?>
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
    <input type="range" min="0" max="255" value="<?= $result['r']?>" id="red">
    <input type="range" min="0" max="255" value="<?= $result['g']?>" id="green">
    <input type="range" min="0" max="255" value="<?= $result['b']?>" id="blue">

    <script>
        // Get the range inputs
        const red = document.getElementById('red');
        const green = document.getElementById('green');
        const blue = document.getElementById('blue');

        let arr = [red, green, blue];
        let arr_name = ['r', 'g', 'b'];

        // When any range move send GET request to IP
        function updateBG() {
            document.body.style.backgroundColor = `rgb(${red.value}, ${green.value}, ${blue.value})`;
        }

        for (let i = 0; i < arr.length; i++) {
            arr[i].addEventListener('input', () => {
                fetch(`/set/?color=${arr_name[i]}&range=${arr[i].value}`);
                updateBG();
            });
        }


        // Set color
        updateBG();
    </script>
</body>
</html>