<?php
// Return json "headers" allow access from any origin and set content type to json
header("Access-Control-Allow-Origin: *");
header("Content-Type: application/json; charset=UTF-8");

// Get parameter ?color={r, g, b}&range={0-255}
$color = $_GET['color'];
$range = $_GET['range'];

$data = require('../database/database.php');

try {
    $conn = new PDO("mysql:host=".$data[0].";dbname=".$data[1], $data[2], $data[3]);
    // set the PDO error mode to exception
    $conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
  
    // Save the color to table led
    $sql = "UPDATE led SET " . $color . " = " . $range;

    // Prepare and execute the query
    $stmt = $conn->prepare($sql);
    $stmt->execute();

    // Return the data as JSON
    echo "{'status': 'ok', '" . $color . "': " . $range . "}";
    
} catch(PDOException $e) {
    echo "{'status': 'error', 'message': 'Connection lost: " . $e->getMessage() . "'}";
}