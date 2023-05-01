<?php
$data = require('../database/database.php');

try {
    $conn = new PDO("mysql:host=".$data[0].";dbname=".$data[1], $data[2], $data[3]);
    // set the PDO error mode to exception
    $conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
  
    // Check if table led is already created
    $sql = "SHOW TABLES LIKE 'led'";
    $stmt = $conn->prepare($sql);
    $stmt->execute();

    // If table led is not created, create it with "id" "r" "g" "b" columns
    if($stmt->rowCount() == 0) {
        $sql = "CREATE TABLE led (
            id INT(6) UNSIGNED AUTO_INCREMENT PRIMARY KEY,
            r INT(3) NOT NULL,
            g INT(3) NOT NULL,
            b INT(3) NOT NULL
        )";
        $conn->exec($sql);

        // Insert default values into table led
        $sql = "INSERT INTO led (r, g, b) VALUES (0, 0, 0)";
        $conn->exec($sql);

        echo "Table led created successfully";
    } else {
        echo "Table led already exists";
    }
} catch(PDOException $e) {
    echo "Installation failed: " . $e->getMessage();
}