<?php
include_once 'models/db.inc';

function findQuestionById($id) {
    global $db;
    $st = $db -> prepare('SELECT * FROM questions join users using (user_id) WHERE id = ?');
    $st -> bindParam(1, $id);
    $st -> execute();
    return $st -> fetch(PDO::FETCH_ASSOC);
}

function findQuestionsByUserId($user_id) {
    global $db;
    $st = $db -> prepare('SELECT * FROM questions WHERE user_id = ? order by date desc limit 10');
    $st -> bindParam(1, $user_id);
    $st -> execute();
    return $st -> fetchAll(PDO::FETCH_ASSOC);
}

function findLatestFiveQuestions() {
    global $db;
    $st = $db -> prepare('SELECT * FROM questions join users using (user_id) order by date desc limit 5');
    $st -> execute();
    return $st -> fetchAll(PDO::FETCH_ASSOC);
}

function addQuestion($title, $content, $tags, $user) {
    global $db;
    $statement = $db -> prepare("INSERT INTO questions (title, content, tags, date, user_id) values (?, ?, ?, datetime('now'),?)");
    $statement -> bindParam(1, $title);
    $statement -> bindParam(2, $content);
    $statement -> bindParam(3, $tags);
    $statement -> bindParam(4, $user);
    $statement -> execute();
    return $db->lastInsertId();
}

function updateQuestion($id, $title, $content, $tags) {
    global $db;
    $statement = $db -> prepare("UPDATE questions SET title = ?, content = ?, tags = ?, date = datetime('now') WHERE id = ?");
    $statement -> bindParam(1, $title);
    $statement -> bindParam(2, $content);
    $statement -> bindParam(3, $tags);
    $statement -> bindParam(4, $id);
    $statement -> execute();
}

function deleteQuestion($id) {
    global $db;
    $statement = $db -> prepare("DELETE FROM questions WHERE id = ?");
    $statement -> bindParam(1, $id);
    $statement -> execute();
}
?>
