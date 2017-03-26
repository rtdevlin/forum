<?php
include_once 'models/model.inc';
include_once 'models/users.inc';

class Question extends Model {
    private $title;
    private $content;
    private $tags;
    private $validator;

    //public function __construct($id, $description, $done = false) {
    public function __construct($fields = array(), $validator){
        parent::__construct($fields);
        $this -> setTitle(safeParam($fields, 'title'));
        $this -> setContent(safeParam($fields, 'content'));
        $this -> setTags(safeParam($fields, 'tags'));
        $this -> setUserId(safeParam($fields, 'user_id'));
        $this -> setInsertTs(safeParam($fields, 'insert_ts'));
        if(!isset($validator)){
          $validator = new Validator();
        }
    }

    public function validate($throw = false) {
        $validator -> required('title', $this -> title, "Title is required");
        $validator -> required('content', $this -> content, "Content is required");
        $validator -> required('user_id', $this -> user_id, "User Id is required");
        if ($throw && $validator -> hasErrors()) {
            throw new IllegalStateException(implode(", ", $validator -> allErrors()));
        }
        return $validator;
    }

    private function clean() {
        $this -> title = htmlentities($this -> title, ENT_QUOTES);
        $this -> content = htmlentities($this -> content, ENT_QUOTES);
        $this -> tags = htmlentities($this -> tags, ENT_QUOTES);
        $this -> user_id = htmlentities($this -> user_id, ENT_QUOTES);
    }

    public function getUserId() {
        return $this -> user_id;
    }

    public function setUserId($user_id) {
        $this -> user_id = $user_id;
        return $this;
    }

    public function getTitle() {
        return $this -> title;
    }

    public function setTitle($title) {
        $this -> title = $title;
        return $this;
    }

    public function getContent() {
        return $this -> content;
    }

    public function setContent($content) {
        $this -> content = $content;
        return $this;
    }

    public function getTags() {
        return $this -> tags;
    }

    public function getInsertTs() {
        return $this -> insert_ts;
    }

    public function setInsertTs($insert_ts) {
        $this -> insert_ts = $insert_ts;
        return $this;
    }

    public function setTags($tags) {
        $this -> tags = $tags;
        return $this;
    }

    public function getUser(){
      return User::findById($this -> user_id);
    }

    static function findById($id) {
        $db = Db::getDb();
        $st = $db -> prepare('SELECT * FROM questions WHERE id = :id');
        $st -> bindParam(':id', $id);
        $st -> execute();
        $row = $st -> fetch(PDO::FETCH_ASSOC);
        return new self($row);
    }

    static function findQuestionsByUserId($user_id) {
        $db = Db::getDb();
        $st = $db -> prepare('SELECT * FROM questions WHERE user_id = ? order by date desc limit 10');
        $st -> bindParam(1, $user_id);
        $st -> execute();
        $rows = $st -> fetchAll(PDO::FETCH_ASSOC);
        return self::fromRows($rows);
    }

    static function findLatestFiveQuestions() {
        $db = Db::getDb();
        $st = $db -> prepare('SELECT * FROM questions order by insert_ts desc limit 5');
        $st -> execute();
        $rows = $st -> fetchAll(PDO::FETCH_ASSOC);
        return self::fromRows($rows);
    }

    function insert() {
        $this -> validate(true);
        $this -> clean();
        $db = Db::getDb();
        $statement = $db -> prepare("INSERT INTO questions (title, content, tags, user_id) values (:title, :content, :tags, :user_id)");
        $statement -> bindParam(':title', $this -> title);
        $statement -> bindParam(':content', $this -> content);
        $statement -> bindParam(':tags', $this -> tags);
        $statement -> bindParam(':user_id', $this -> user_id);
        $statement -> execute();
        $this -> id = $db -> lastInsertId();
        return $this;
    }

    function update() {
        $this -> validate(true);
        $this -> clean();
        $db = Db::getDb();
        $statement = $db -> prepare("UPDATE questions SET title = :title, content = :content, tags = :tags WHERE id = :id");
        $statement -> bindParam(':title', $this -> title);
        $statement -> bindParam(':content', $this -> content);
        $statement -> bindParam(':tags', $this -> tags);
        $statement -> bindParam(':id', $this -> id);
        $statement -> execute();
        return $this;
    }

    function delete() {
        $db = Db::getDb();
        $statement = $db -> prepare("DELETE FROM questions WHERE id = :id");
        $statement -> bindParam(':id', $this -> id);
        $statement -> execute();
    }
}
?>
