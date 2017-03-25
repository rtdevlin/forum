<?php
global $db;
try {
    $db = new PDO('sqlite:Forum.db3');
} catch (PDOException $e) {
    die("Could not open database. " . $e->getMessage());
}

function adHocQuery($q) {
    global $db;
    $st = $db -> prepare($q);
    $st -> execute();
    return $st -> fetchAll(PDO::FETCH_ASSOC);
}
?>
