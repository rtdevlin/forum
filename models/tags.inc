<?php
include_once 'models/model.inc';
include_once 'models/users.inc';
include_once 'models/validator.inc';

class Tag extends Model {
    private $name;
    private $validator;

    //public function __construct($id, $description, $done = false) {
    public function __construct($fields = array(), $validator = null){
        parent::__construct($fields);
        $this -> setName(safeParam($fields, 'name'));
        if(!isset($validator)){
          $this -> validator = new Validator();
        }
        else {
          $this -> validator = $validator;
        }
    }

    public function validate($throw = false) {
        $this -> validator -> required('name', $this -> name, "Name is required");
        if ($throw && $this -> validator -> hasErrors()) {
            throw new Exception(implode(", ", $this -> validator -> allErrors()));
        }
        return $this -> validator;
    }

    private function clean() {
        $this -> name = htmlentities($this -> name, ENT_QUOTES);
    }

    public function getName() {
        return $this -> name;
    }

    public function setName($name) {
        $this -> name = $name;
        return $this;
    }

    static function findById($id) {
        $db = Db::getDb();
        $st = $db -> prepare('SELECT * FROM tags WHERE id = :id');
        $st -> bindParam(':id', $id);
        $st -> execute();
        $row = $st -> fetch(PDO::FETCH_ASSOC);
        return new self($row);
    }

    static function findByName($name) {
        if(!$db){
          $db = Db::getDb();
        }
        $st = $db -> prepare('SELECT * FROM tags WHERE name = :name');
        $st -> bindParam(':name', $name);
        $st -> execute();
        $row = $st -> fetch(PDO::FETCH_ASSOC);
        return new self($row);
    }

    static function findOrCreateByName($params) {
        if(!$db){
          $db = Db::getDb();
        }
        $name = $params['name'];
        $current_row = Tag::findByName($name);
        if($current_row -> getId()){
          return $current_row;
        }
        else{
          $new_tag = new Tag($params);
          return $new_tag -> insert();
        }
    }

    function insert() {
        $this -> validate(true);
        $this -> clean();
        if(!$db){
          $db = Db::getDb();
        }
        $statement = $db -> prepare("INSERT INTO tags (name) values (:name)");
        $statement -> bindParam(':name', $this -> name);
        $statement -> execute();
        $this -> id = $db -> lastInsertId();
        return $this;
    }

    function update() {
        $this -> validate(true);
        $this -> clean();
        $db = Db::getDb();
        $statement = $db -> prepare("UPDATE tags SET name = :name");
        $statement -> bindParam(':name', $this -> name);
        $statement -> execute();
        return $this;
    }

    function delete() {
        $db = Db::getDb();
        $statement = $db -> prepare("DELETE FROM tags WHERE id = :id");
        $statement -> bindParam(':id', $this -> id);
        $statement -> execute();
    }
}
?>
