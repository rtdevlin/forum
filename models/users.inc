<?php
include_once 'models/db.inc';

function isValidUser($username, $password) {
  global $db;
    $st = $db -> prepare('SELECT * FROM users WHERE email = ?');
    $st -> bindParam(1, $username);
    $st -> execute();
    $user = $st -> fetch(PDO::FETCH_ASSOC);
    if (isset($user)) {
      return $user['password'] === $password;
    }
    else {
      return false;
    }
}
function userExists($username) {
  global $db;
    $st = $db -> prepare('SELECT count(*) as cnt FROM users WHERE email = ?');
    $st -> bindParam(1, $username);
    $st -> execute();
    $count = $st -> fetch(PDO::FETCH_ASSOC);
    if (isset($count) ) {
      return $count['cnt'] == 1;
    }
    else {
      return false;
    }
}

function findUserByEmail($email) {
    global $db;
    $st = $db -> prepare('SELECT * FROM users WHERE email = ?');
    $st -> bindParam(1, $email);
    $st -> execute();
    return $st -> fetch(PDO::FETCH_ASSOC);
}

function findUserById($id) {
    global $db;
    $st = $db -> prepare('SELECT * FROM users WHERE user_id = ?');
    $st -> bindParam(1, $id);
    $st -> execute();
    return $st -> fetch(PDO::FETCH_ASSOC);
}

function addUser($first_name, $last_name, $email, $password) {
    global $db;
    $statement = $db -> prepare("INSERT INTO users (first_name, last_name, email, password) values (?, ?, ?, ?)");
    $statement -> bindParam(1, $first_name);
    $statement -> bindParam(2, $last_name);
    $statement -> bindParam(3, $email);
    $statement -> bindParam(4, $password);
    $statement -> execute();
    return $db->lastInsertId();
}

function updateUser($id, $first_name, $last_name, $email, $password) {
    global $db;
    $statement = $db -> prepare("UPDATE users SET first_name = ?, last_name = ?, email = ?, date = datetime('now') WHERE id = ?");
    $statement -> bindParam(1, $first_name);
    $statement -> bindParam(2, $last_name);
    $statement -> bindParam(3, $email);
    $statement -> bindParam(4, $id);
    $statement -> bindParam(4, $password);
    $statement -> execute();
}

function deleteUser($id) {
    global $db;
    $statement = $db -> prepare("DELETE FROM users WHERE id = ?");
    $statement -> bindParam(1, $id);
    $statement -> execute();
}
?>
