<?php
require_once "models/db.inc";
require_once "include/util.inc";
require_once "models/validator.inc";

abstract class Model {
    protected $id;

    public function __construct($fields = array()) {
        $id = safeParam($fields, 'id');
        if ($id && is_numeric($id)) {
            $this -> setId($id);
        }
    }

    public static function fromRows($rows) {
        $class = get_called_class();
        $result = array();
        foreach ($rows as $row) {
            $result[] = new $class($row);
        }
        return $result;
    }

    public function getId() {
        return $this -> id;
    }

    public function setId($id) {
        $this -> id = $id;
        return $this;
    }

    protected static function adHocQuery($q) {
        $db = Db::getDb();
        $st = $db -> prepare($q);
        $st -> execute();
        return $st -> fetchAll(PDO::FETCH_ASSOC);
    }

    public function insertOrUpdate() {
        $db = Db::getDb();
        if ($this -> getId()) {
            $this -> update();
        } else {
            $this -> insert();
        }
        return $this;
    }

    public abstract function insert();
    public abstract function delete();
    public abstract function update();

}
?>
