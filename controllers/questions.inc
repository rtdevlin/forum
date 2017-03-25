<?php
include_once "include/util.inc";
include_once "models/questions.inc";

define("REQUIRED_PARAMS", array('title', 'content'));



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
        die("No question id specified");
    }
    $question = findQuestionById($id);
    if (!$question) {
        die("No question with id $id found.");
    }
    $authenticated = authenticateUser($question['user_id']);
    // @formatter:off
    renderTemplate(
        "views/question_view.inc",
        array(
            'title' => $question['title'],
            'question' => $question,
            'auth' => $authenticated,
            'wtf' => $user_id
        )
    );
    // @formatter:on
}

function get_list($params) {
    $questions = findLatestFiveQuestions();
    // @formatter:off
    renderTemplate(
        "views/index.inc",
        array(
            'title' => 'My Questions and Answers',
            'questions' => $questions,
        )

    );
    // @formatter:on
}

function get_edit($params) {
  ensureLoggedIn();
    $id = safeParam($params, 0, false);
    if (!$id) {
        die("No question specified");
    }
    $question = findQuestionById($id);
    if (!$question) {
        die("No question found.");
    }
    $authenticated = authenticateUser($question['user_id']);
    // @formatter:off
    if($authenticated){
      renderTemplate(
          "views/question_edit.inc",
          array(
              'title' => 'Editing Question',
              'question' => $question
          )
      );
    }
    else {
      redirectRelative('index');
    }
}

function get_add($params) {
    // @formatter:off
  ensureLoggedIn();
    renderTemplate(
        "views/question_add.inc",
        array(
            'title' => 'Add A Question'
        )
    );
    // @formatter:on
}

function post_add($params) {
  ensureLoggedIn();
  if(!requiredParamsPresent($params)){
    $request_string = "views/question_add.inc";
    validateChanges($params, $request_string,
      array (
        'title' => 'Add A Question',
        'question' => $params
      )
    );
  }
  else {
    $title = htmlentities($_POST['title']);
    $content = htmlentities($_POST['content']);
    $tags = htmlentities($_POST['tags']);
    $user_id = current_user()['user_id'];
    addQuestion($title, $content, $tags, $user_id);
    redirectRelative("index");
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
    $request_string = "views/question_edit.inc";
    validateChanges($params, $request_string,
      array (
        'title' => 'Editing Question',
        'question' => $params
      )
    );
  }
  else{
    $id = $_POST['id'];
    $title = htmlentities($_POST['title']);
    $content = htmlentities($_POST['content']);
    $tags = htmlentities($_POST['tags']);
    updateQuestion($id, $title, $content, $tags);
    redirectRelative("questions/view/$id");
  }
}

function get_delete($params) {
  ensureLoggedIn();
    $id = safeParam($params, 0, false);
    if (!$id) {
        die("No question specified");
    }
    $question = findQuestionById($id);
    if (!$question) {
        die("No question found.");
    }
    $authenticated = authenticateUser($question['user_id']);
    if($authenticated){
      deleteQuestion($id);
    }
    redirectRelative("index");
}
?>
