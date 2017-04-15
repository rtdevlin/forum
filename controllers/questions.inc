<?php
include_once "include/util.inc";
include_once "models/questions.inc";
include_once "models/tags.inc";
include_once "models/answers.inc";
include_once "models/question_tags.inc";


function get_view($params) {
    $id = safeParam($params, 0, false);
    if ($id === false) {
        die("No question id specified");
    }
    $question = Question::findById($id);
    $tags = $question -> getTags();
    $answers = Answer::findByQuestionId($id);
    if (!$question) {
        die("No question with id $id found.");
    }
    $authenticated = authenticateUser($question -> getUserId());
    // @formatter:off
    renderTemplate(
        "views/question_view.inc",
        array(
            'title' => $question -> getTitle(),
            'question' => $question,
            'tags' => $tags,
            'answers' => $answers,
            'auth' => $authenticated,
        )
    );
    // @formatter:on
}

function get_list($params) {
    $questions = Question::findLatestFiveQuestions();
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
    $question = Question::findById($id);
    if (!$question) {
        die("No question found.");
    }
    $authenticated = authenticateUser($question -> getUserId());
    if(!$authenticated){
      Authenticator::instance() -> ensure('edit_question');
      $authenticated = true;
    }
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
  $question = new Question($params);
  ensureLoggedIn();
  renderTemplate(
      "views/question_add.inc",
      array(
          'title' => 'Add A Question',
          'question' => $question
      )
  );
    // @formatter:on
}

function post_add($params) {
  ensureLoggedIn();
  $question = new Question($params);
  $split_tags = splitTags($params['tags']);
  $validator = $question -> validate();
  if($validator -> hasErrors()){
    renderTemplate(
      "views/question_add.inc",
      array (
        'title' => 'Add A Question',
        'question' => $question,
        'errors' => $validator -> allErrors()
      )
    );
  }
  else {
    $question -> insert();
    $tags = insertTags($split_tags);
    buildQuestionTagBridge($question, $tags);
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
  $question = new Question($params);
  $split_tags = splitTags($params['tags']);
  $validator = $question -> validate();
  if($validator -> hasErrors()){
    renderTemplate(
      "views/question_edit.inc",
      array (
        'title' => 'Editing Question',
        'question' => $question,
        'errors' => $validator -> allErrors()
      )
    );
  }
  else{
    $question -> update();
    $id = $question -> getId();
    $tags = insertTags($split_tags);
    resetTags($id);
    buildQuestionTagBridge($question, $tags);
    redirectRelative("questions/view/$id");
  }
}

function get_delete($params) {
  ensureLoggedIn();
    $id = safeParam($params, 0, false);
    if (!$id) {
        die("No question specified");
    }
    $question = Question::findById($id);
    if (!$question) {
        die("No question found.");
    }
    $authenticated = authenticateUser($question -> getUserId());
    if(!$authenticated){
      Authenticator::instance() -> ensure('delete_question');
      $authenticated = true;
    }
    if($authenticated){
      resetTags($question->getId());
      Answer::deleteByQuestionId($question->getId());
      $question -> delete();
    }
    redirectRelative("index");
}
?>
