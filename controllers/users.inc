<?php
include_once "include/util.inc";
include_once "models/users.inc";
include_once "models/questions.inc";

define("REQUIRED_PARAMS", array('first_name', 'last_name', 'email', 'password'));



function safeParam($arr, $index, $default) {
    if ($arr && isset($arr[$index])) {
        return $arr[$index];
    }
    return $default;
}
function requiredParamsPresent($params){
  $present = true;
  foreach(REQUIRED_PARAMS as $param){
    $present = empty($params[$param]) ? false : true;
    if(!$present){
      return $present;
    }
  }
  return $present;
}

function get_view($params) {
    $id = safeParam($params, 0, false);
    if ($id === false) {
        die("No user id specified");
    }
    $authenticated = authenticateUser($id);
    $user = findUserById($id);
    if (!$user) {
        die("No user with id $id found.");
    }
    $questions = findQuestionsByUserId($user['user_id']);
    // @formatter:off
    renderTemplate(
        "views/user_view.inc",
        array(
            'title' => "$user[first_name]  $user[last_name]",
            'user' => $user,
            'questions' => $questions,
            'auth' => $authenticated
        )
    );
    // @formatter:on
}

function get_list($params) {
}

function get_edit($params) {
  ensureLoggedIn();
    $id = safeParam($params, 0, false);
    if (!$id) {
        die("No user specified");
    }
    $authenticated = authenticateUser($id);
    $user = findUserById($id);
    if (!$user) {
        die("No user found.");
    }
    // @formatter:off
    if($authenticated){
      renderTemplate(
          "views/user_edit.inc",
          array(
              'title' => 'Editing User',
              'user' => $user,
          )
      );
    }
    else {
      redirectRelative('index');
    }
    // @formatter:on
}

function get_add($params) {
    // @formatter:off
    renderTemplate(
        "views/user_add.inc",
        array(
            'title' => 'Register!'
        )
    );
    // @formatter:on
}

function post_add($params) {
  if(!requiredParamsPresent($params)){
    $request_string = "views/user_add.inc";
    validateChanges($params, $request_string,
      array (
        'title' => 'Add A User',
        'user' => $params
      )
    );
  }
  else {
    $first_name = htmlentities($_POST['first_name']);
    $last_name = htmlentities($_POST['last_name']);
    $email = htmlentities($_POST['email']);
    $password = htmlentities($_POST['password']);
    if(userExists($email)){
      renderTemplate(
          "views/login_form.inc",
          array(
              'title' => 'Login',
              'errors' => array("Email $email already exists. Please Login")
          )
      );
    }
    else {
      addUser($first_name, $last_name, $email, $password);
          $_SESSION['loggedin'] = true;
          if (isset($_SESSION['redirect'])) {
              $redirect = $_SESSION['redirect'];
              redirect($redirect);
              exit();
          }
          redirectRelative("index");
    }
  }
}

function validate_present($elements) {
    $errors = '';
    foreach ($elements as $element) {
        if (!isset($_POST[$element])) {
            $errors .= "Missing $element\n";
        }
    }
    return $errors;
}

function post_update($params) {
  ensureLoggedIn();
  if(!requiredParamsPresent($params)){
    $request_string = "views/user_edit.inc";
    validateChanges($params, $request_string,
      array (
        'title' => 'Editing User',
        'user' => $params
      )
    );
  }
  else{
    $user_id = $_POST['user_id'];
    $first_name = htmlentities($_POST['first_name']);
    $last_name = htmlentities($_POST['last_name']);
    $email = htmlentities($_POST['email']);
    $password = htmlentities($_POST['password']);
    if(userExists($email)){
      renderTemplate(
          "views/user_edit.inc",
          array(
              'title' => 'Edit User',
              'errors' => array("Email $email already exists."),
              'user' => $params
          )
      );
    }
    else {
      updateUser($user_id, $first_name, $last_name, $email, $password);
      redirectRelative("users/view/$id");
    }
  }
}

function get_delete($params) {
    ensureLoggedIn();
    $id = safeParam($params, 0, false);
    if (!$id) {
        die("No user specified");
    }
    $user = findUserById($id);
    if (!$user) {
        die("No user found.");
    }
    $authenticated = authenticateUser($id);
    if($authenticated){
      deleteUser($id);
    }
    redirectRelative("index");
}
?>
