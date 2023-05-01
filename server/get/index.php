<?php
// Return json "headers" allow access from any origin and set content type to json
header("Access-Control-Allow-Origin: *");
header("Content-Type: application/json; charset=UTF-8");

$data = require('../database/database.php');

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

    // Return the data as JSON as format {"status":"ok", "r": 0, "g": 0, "b": 0}
    echo "{'status': 'ok', 'r': " . $result['r'] . ", 'g': " . $result['g'] . ", 'b': " . $result['b'] . "}";
    
} catch(PDOException $e) {
    echo "{'status': 'error', 'message': 'Connection lost: " . $e->getMessage() . "'}";
}