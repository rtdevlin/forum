<?php
include_once 'models/model.inc';
include_once 'models/users.inc';
include_once 'models/permission.inc';
include_once 'models/validator.inc';

class Group extends Model {

    protected $name;

    function __construct($fields = array()) {
        parent::__construct($fields);
        $this -> setName(safeParam($fields, 'name'));
    }

    public function validate($throw = false) {
        $validator = new Validator();
        $validator -> required('name', $this -> name, "Group name is required");
        if ($throw && $validator -> hasErrors()) {
            throw new Exception(implode(", ", $validator -> allErrors()));
        }
        return $validator;
    }

    private function clean() {
        $this -> name = htmlentities($this -> name, ENT_QUOTES);
    }

    public function setName($name) {
        $this -> name = trim($name);
        return $this;
    }

    public function getName() {
        return $this -> name;
    }

    public static function findAll() {
        $db = Db::getDb();
        $st = $db -> prepare("SELECT * FROM groups ORDER BY name");
        $st -> execute();
        return self::fromRows($st -> fetchAll(PDO::FETCH_ASSOC));
    }

    public static function findById($id) {
        $db = Db::getDb();
        $st = $db -> prepare("SELECT * FROM groups WHERE id = :id");
        $st -> bindParam(':id', $id);
        $st -> execute();
        return new Group($st -> fetch(PDO::FETCH_ASSOC));
    }

    public static function findByName($name) {
        $db = Db::getDb();
        $st = $db -> prepare("SELECT * FROM groups WHERE name = :name");
        $st -> bindParam(':name', $name);
        $st -> execute();
        return new Group($st -> fetch(PDO::FETCH_ASSOC));
    }

    public function insert() {
        $db = Db::getDb();
        $this -> validate(true);
        $this -> clean();
        $statement = $db -> prepare("INSERT INTO groups (name) VALUES (:name)");
        $statement -> bindParam(':name', $this -> name);
        $statement -> execute();
        $this -> setId($db -> lastInsertId());
        return $this;
    }

    public function update() {
        $db = Db::getDb();
        $this -> validate(true);
        $this -> clean();
        $statement = $db -> prepare("UPDATE groups SET name=:name WHERE id=:id");
        $statement -> bindParam(':name', $this -> name);
        $statement -> bindParam(':id', $this -> id);
        $statement -> execute();
        return $this;
    }

    public function delete() {
        self::deleteById($this -> getId());
    }

    private static function deleteById($id) {
        $db = Db::getDb();
        $statement = $db -> prepare("DELETE FROM groups WHERE id = :id");
        $statement -> bindParam(':id', $id);
        $statement -> execute();
    }

    public static function findByUserId($userId) {
        $db = Db::getDb();
        $statement = $db -> prepare("SELECT * FROM groups where groups.id in (SELECT groups.id from groups, user_groups WHERE groups.id = user_groups.group_id AND user_groups.user_id = :userId) order by name");
        $statement -> bindParam(':userId', $userId);
        $statement -> execute();
        return self::fromRows($statement->fetchAll(PDO::FETCH_ASSOC));
    }

    public static function findByNotUserId($userId) {
        $db = Db::getDb();
        $statement = $db -> prepare("SELECT * FROM groups where groups.id not in (SELECT groups.id from groups, user_groups WHERE groups.id = user_groups.group_id AND user_groups.user_id = :userId) order by name");
        $statement -> bindParam(':userId', $userId);
        $statement -> execute();
        return self::fromRows($statement->fetchAll(PDO::FETCH_ASSOC));
    }

    public function addUser($user) {
        $db = Db::getDb();
        $statement = $db -> prepare("INSERT INTO user_groups (group_id, user_id) VALUES (:groupId, :userId)");
        $statement -> bindValue(':groupId', $this -> getId());
        $statement -> bindValue(':userId', $user -> getId());
        $statement -> execute();
    }

    public function removeUser($user) {
        $db = Db::getDb();
        $statement = $db -> prepare("DELETE FROM user_groups WHERE group_id = :groupId AND user_id = :userId");
        $statement -> bindValue(':groupId', $this -> getId());
        $statement -> bindValue(':userId', $user -> getId());
        $statement -> execute();
    }

    public function addPermission($permission) {
        $db = Db::getDb();
        $statement = $db -> prepare("INSERT INTO group_permissions (group_id, permission_id) VALUES (:groupId, :permissionId)");
        $statement -> bindValue(':groupId', $this -> getId());
        $statement -> bindValue(':permissionId', $permission -> getId());
        $statement -> execute();
    }

    public function removePermission($permission) {
        $db = Db::getDb();
        $statement = $db -> prepare("DELETE FROM group_permissions WHERE permission_id = :permissionId AND group_id = :groupId");
        $statement -> bindValue(':groupId', $this -> getId());
        $statement -> bindValue(':permissionId', $permission -> getId());
        $statement -> execute();
    }

    public function getMembers() {
        $db = Db::getDb();
        $statement = $db -> prepare("SELECT users.id AS id, users.first_name, users.last_name, users.password AS password FROM users, user_groups WHERE users.id = user_groups.user_id and user_groups.group_id = :id ORDER BY last_name, first_name");
        $statement -> bindParam(':id', $this -> id);
        $statement -> execute();
        $rows = $statement -> fetchAll(PDO::FETCH_ASSOC);
        return User::fromRows($rows);
    }

    public function getNonMembers() {
        $db = Db::getDb();
        $statement = $db -> prepare("SELECT * FROM users WHERE users.id not in (SELECT users.id FROM users, user_groups WHERE users.id = user_groups.user_id and user_groups.group_id = :id) ORDER BY last_name, first_name;");
        $statement -> bindParam(':id', $this -> id);
        $statement -> execute();
        $rows = $statement -> fetchAll(PDO::FETCH_ASSOC);
        return User::fromRows($rows);
    }

    public function getPermissions() {
        $db = Db::getDb();
        $statement = $db -> prepare("SELECT permissions.id AS id, permissions.name as name FROM permissions, group_permissions WHERE permissions.id = group_permissions.permission_id and group_permissions.group_id = :id ORDER BY name");
        $statement -> bindParam(':id', $this -> id);
        $statement -> execute();
        $rows = $statement -> fetchAll(PDO::FETCH_ASSOC);
        return Permission::fromRows($rows);
    }

    public function getNonPermissions() {
        $db = Db::getDb();
        $statement = $db -> prepare("SELECT * FROM permissions WHERE permissions.id not in (SELECT permissions.id FROM permissions, group_permissions WHERE permissions.id = group_permissions.permission_id and group_permissions.group_id = :id) ORDER BY name;");
        $statement -> bindParam(':id', $this -> id);
        $statement -> execute();
        $rows = $statement -> fetchAll(PDO::FETCH_ASSOC);
        return Permission::fromRows($rows);
    }

}
?>
