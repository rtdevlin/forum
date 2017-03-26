<?php
include_once 'models/model.inc';
include_once 'models/questions.inc';
include_once 'models/tags.inc';
include_once 'models/validator.inc';

class QuestionTag extends Model {
    private $question_id;
    private $tag_id;
    private $validator;

    //public function __construct($id, $description, $done = false) {
    public function __construct($fields = array(), $validator = null){
        $this -> setQuestionId(safeParam($fields, 'question_id'));
        $this -> setTagId(safeParam($fields, 'tag_id'));
        if(!isset($validator)){
          $this -> validator = new Validator();
        }
        else {
          $this -> validator = $validator;
        }
    }

    public function validate($throw = false) {
        $this -> validator -> required('question_id', $this -> question_id, "question_id is required");
        $this -> validator -> required('tag_id', $this -> tag_id, "tag_id is required");
        if ($throw && $this -> validator -> hasErrors()) {
            throw new Exception(implode(", ", $this -> validator -> allErrors()));
        }
        return $this -> validator;
    }

    private function clean() {
        $this -> question_id = htmlentities($this -> question_id, ENT_QUOTES);
        $this -> tag_id = htmlentities($this -> tag_id, ENT_QUOTES);
    }

    public function getQuestionId() {
        return $this -> question_id;
    }

    public function setQuestionId($question_id) {
        $this -> question_id = $question_id;
        return $this;
    }

    public function getTagId() {
        return $this -> tag_id;
    }

    public function setTagId($tag_id) {
        $this -> tag_id = $tag_id;
        return $this;
    }


    static function findByQuestionId($question_id) {
        $db = Db::getDb();
        $st = $db -> prepare('SELECT * FROM question_tags WHERE question_id = :question_id');
        $st -> bindParam(':question_id', $question_id);
        $st -> execute();
        $rows = $st -> fetchAll(PDO::FETCH_ASSOC);
        return self::fromRows($rows);
    }

    static function findByTagId($tag_id) {
        $db = Db::getDb();
        $st = $db -> prepare('SELECT * FROM question_tags WHERE tag_id = :tag_id');
        $st -> bindParam(':tag_id', $tag_id);
        $st -> execute();
        $rows = $st -> fetchAll(PDO::FETCH_ASSOC);
        return self::fromRows($rows);
    }



    function insert() {
        $this -> validate(true);
        $this -> clean();
        $db = Db::getDb();
        $statement = $db -> prepare("INSERT INTO question_tags (question_id, tag_id) values (:question_id, :tag_id)");
        $statement -> bindParam(':question_id', $this -> question_id);
        $statement -> bindParam(':tag_id', $this -> tag_id);
        $statement -> execute();
        $this -> id = $db -> lastInsertId();
        return $this;
    }

    function update() {
      #$this -> validate(true);
      #$this -> clean();
      #$db = Db::getDb();
      #$statement = $db -> prepare("UPDATE questions SET title = :title, content = :content, tags = :tags WHERE id = :id");
      #$statement -> bindParam(':title', $this -> title);
      #$statement -> bindParam(':content', $this -> content);
      #$statement -> bindParam(':tags', $this -> tags);
      #$statement -> bindParam(':id', $this -> id);
      #$statement -> execute();
      #return $this;
    }

    function delete() {
        $db = Db::getDb();
        $statement = $db -> prepare("DELETE FROM question_tags WHERE question_id = :question_id and tag_id = :tag_id");
        $statement -> bindParam(':question_id', $this -> question_id);
        $statement -> bindParam(':tag_id', $this -> tag_id);
        $statement -> execute();
    }

    static function deleteByQuestionId($question_id) {
        $db = Db::getDb();
        $statement = $db -> prepare("DELETE FROM question_tags WHERE question_id = :question_id");
        $statement -> bindParam(':question_id', $question_id);
        $statement -> execute();
    }
}
?>
