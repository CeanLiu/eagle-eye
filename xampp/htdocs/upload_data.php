<?php

if(isset($_GET["file_path"])) {
   $file_path = $_GET["file_path"]; // Get file path value from HTTP GET

   $servername = "localhost";
   $username = "eagleeye";
   $password = "eagleeyeproject";
   $database_name = "db_eagleeye";

   // Create MySQL connection from PHP to MySQL server
   $connection = new mysqli($servername, $username, $password, $database_name);

   // Check connection
   if ($connection->connect_error) {
      die("MySQL connection failed: " . $connection->connect_error);
   }

   // Prepare and bind to prevent SQL injection
   $stmt = $connection->prepare("INSERT INTO tbl_data (file_path) VALUES (?)");
   $stmt->bind_param("s", $file_path); // "s" indicates a string type

   // Execute the statement
   if ($stmt->execute() === TRUE) {
      echo "New record created successfully";
   } else {
      echo "Error: " . $stmt->error;
   }

   $stmt->close();
   $connection->close();
} else {
   echo "file_path is not set in the HTTP request";
}
?>
