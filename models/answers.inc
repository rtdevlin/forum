<?php
include_once 'models/model.inc';
include_once 'models/users.inc';
include_once 'models/question_tags.inc';
include_once 'models/tags.inc';
include_once 'models/validator.inc';

class Answer extends Model {
    private $user_id;
    private $question_id;
    private $content;
    private $validator;

    //public function __construct($id, $description, $done = false) {
    public function __construct($fields = array(), $validator = null){
        parent::__construct($fields);
        $this -> setContent(safeParam($fields, 'content'));
        $this -> setUserId(safeParam($fields, 'user_id'));
        $this -> setQuestionId(safeParam($fields, 'question_id'));
        $this -> setInsertTs(safeParam($fields, 'insert_ts'));
        if(!isset($validator)){
          $this -> validator = new Validator();
        }
        else {
          $this -> validator = $validator;
        }
    }

    public function validate($throw = false) {
        $this -> validator -> required('content', $this -> content, "Content is required");
        $this -> validator -> required('user_id', $this -> user_id, "User Id is required");
        $this -> validator -> required('question_id', $this -> question_id, "User Id is required");
        if ($throw && $this -> validator -> hasErrors()) {
            throw new IllegalStateException(implode(", ", $this -> validator -> allErrors()));
        }
        return $this -> validator;
    }

    private function clean() {
        $this -> content = htmlentities($this -> content, ENT_QUOTES);
        $this -> user_id = htmlentities($this -> user_id, ENT_QUOTES);
        $this -> question_id = htmlentities($this -> question_id, ENT_QUOTES);
    }

    public function auth(){
      $authenticated = $this->getUserId() === current_user();
      return $authenticated;
    }

    public function getUserId() {
        return $this -> user_id;
    }

    public function setUserId($user_id) {
        $this -> user_id = $user_id;
        return $this;
    }

    public function getQuestionId() {
        return $this -> question_id;
    }

    public function setQuestionId($question_id) {
        $this -> question_id = $question_id;
        return $this;
    }

    public function getContent() {
        return $this -> content;
    }

    public function setContent($content) {
        $this -> content = $content;
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
        $st = $db -> prepare("SELECT * FROM answers WHERE id = (:id)");
        $st -> bindParam(':id', $id);
        $st -> execute();
        $rows = $st -> fetch(PDO::FETCH_ASSOC);
        return new self($rows);
    }

    static function findByQuestionId($id) {
        $db = Db::getDb();
        $st = $db -> prepare("SELECT * FROM answers WHERE question_id = (:id)");
        $st -> bindParam(':id', $id);
        $st -> execute();
        $rows = $st -> fetchAll(PDO::FETCH_ASSOC);
        return self::fromRows($rows);
    }

    static function findByIds($ids) {
        $db = Db::getDb();
        $question_marks = implode(',', array_fill(1, count($ids), '?'));
        $st = $db -> prepare("SELECT * FROM answers WHERE id in ($question_marks)");
        $st -> execute($ids);
        $rows = $st -> fetchAll(PDO::FETCH_ASSOC);
        return self::fromRows($rows);
    }

    function insert() {
        $this -> validate(true);
        $this -> clean();
        $db = Db::getDb();
        $statement = $db -> prepare("INSERT INTO answers (content, question_id, user_id) values (:content, :question_id, :user_id)");
        $statement -> bindParam(':content', $this -> content);
        $statement -> bindParam(':question_id', $this -> question_id);
        $statement -> bindParam(':user_id', $this -> user_id);
        $statement -> execute();
        $this -> id = $db -> lastInsertId();
        return $this;
    }

    function update() {
        $this -> validate(true);
        $this -> clean();
        $db = Db::getDb();
        $statement = $db -> prepare("UPDATE answers SET content = :content WHERE id = :id");
        $statement -> bindParam(':content', $this -> content);
        $statement -> bindParam(':id', $this -> id);
        $statement -> execute();
        return $this;
    }

    function delete() {
        $db = Db::getDb();
        $statement = $db -> prepare("DELETE FROM answers WHERE id = :id");
        $statement -> bindParam(':id', $this -> id);
        $statement -> execute();
    }

    function deleteByUserId($user_id){
        $db = Db::getDb();
        $statement = $db -> prepare("DELETE FROM answers WHERE user_id = :id");
        $statement -> bindParam(':id', $user_id);
        $statement -> execute();
    }

    function deleteByQuestionId($question_id){
        $db = Db::getDb();
        $statement = $db -> prepare("DELETE FROM answers WHERE question_id = :id");
        $statement -> bindParam(':id', $question_id);
        $statement -> execute();
    }
}
?>

