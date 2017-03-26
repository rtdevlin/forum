<?php
include_once 'models/model.inc';
include_once 'models/users.inc';
include_once 'models/question_tags.inc';
include_once 'models/tags.inc';
include_once 'models/validator.inc';

class Question extends Model {
    private $title;
    private $content;
    private $validator;

    //public function __construct($id, $description, $done = false) {
    public function __construct($fields = array(), $validator = null){
        parent::__construct($fields);
        $this -> setTitle(safeParam($fields, 'title'));
        $this -> setContent(safeParam($fields, 'content'));
        $this -> setUserId(safeParam($fields, 'user_id'));
        $this -> setInsertTs(safeParam($fields, 'insert_ts'));
        if(!isset($validator)){
          $this -> validator = new Validator();
        }
        else {
          $this -> validator = $validator;
        }
    }

    public function validate($throw = false) {
        $this -> validator -> required('title', $this -> title, "Title is required");
        $this -> validator -> required('content', $this -> content, "Content is required");
        $this -> validator -> required('user_id', $this -> user_id, "User Id is required");
        if ($throw && $this -> validator -> hasErrors()) {
            throw new IllegalStateException(implode(", ", $this -> validator -> allErrors()));
        }
        return $this -> validator;
    }

    private function clean() {
        $this -> title = htmlentities($this -> title, ENT_QUOTES);
        $this -> content = htmlentities($this -> content, ENT_QUOTES);
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
      $bridge_rows = QuestionTag::findByQuestionId($this -> getId());
      $tags = array();
      if(!$bridge_rows){
        foreach($bridge_rows as $row){
          $tag_name = Tags::findById($row -> getTagId() -> getName());
          $tags[] = $tag_name;
        }
      }
      $this -> tags = implode(' ', $tags);
      return $this -> tags;
    }

    public function setTags($tags) {
      $parsed_tags = explode(' ', $tags);
      foreach($parsed_tags as $tag){
        $tag_row = Tag::findByName($tag);
        if(!$tag_row){
          $new_tag = new Tag($tag);
          $new_tag -> insert();
          $question_tag = new QuestionTag($this -> getId(), $new_tag -> getId());
          $question_tag -> insert();
        }
        else {
          $question_tag = new QuestionTag($this -> getId(), $tag_row -> getId());
          $question_tag -> insert();
        }
      }
        $this -> tags = getTags();
        return $this;
    }

    public function getInsertTs() {
        return $this -> insert_ts;
    }

    public function setInsertTs($insert_ts) {
        $this -> insert_ts = $insert_ts;
        return $this;
    }


    public function getUser(){
      $user = User::findById($this -> user_id);
      return $user;
    }

    static function findById($id) {
        $db = Db::getDb();
        $st = $db -> prepare('SELECT * FROM questions WHERE id = :id');
        $st -> bindParam(':id', $id);
        $st -> execute();
        $row = $st -> fetch(PDO::FETCH_ASSOC);
        return new self($row);
    }

    static function findByTag($tag) {
        $db = Db::getDb();
        $st = $db -> prepare('SELECT * FROM questions WHERE tags like :id');
        $st -> bindParam(':id', $id);
        $st -> execute();
        $row = $st -> fetch(PDO::FETCH_ASSOC);
        return new self($row);
    }

    static function findQuestionsByUserId($user_id) {
        $db = Db::getDb();
        $st = $db -> prepare('SELECT * FROM questions WHERE user_id = :user_id order by insert_ts desc limit 10');
        $st -> bindParam(':user_id', $user_id);
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
        $statement = $db -> prepare("INSERT INTO questions (title, content, user_id) values (:title, :content, :user_id)");
        $statement -> bindParam(':title', $this -> title);
        $statement -> bindParam(':content', $this -> content);
        $statement -> bindParam(':user_id', $this -> user_id);
        $statement -> execute();
        $this -> id = $db -> lastInsertId();
        return $this;
    }

    function update() {
        $this -> validate(true);
        $this -> clean();
        $db = Db::getDb();
        $statement = $db -> prepare("UPDATE questions SET title = :title, content = :content, WHERE id = :id");
        $statement -> bindParam(':title', $this -> title);
        $statement -> bindParam(':content', $this -> content);
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
