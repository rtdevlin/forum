<?php
include_once "include/util.inc";
include_once "models/questions.inc";
include_once "models/answers.inc";
include_once "models/tags.inc";
include_once "models/question_tags.inc";

function post_add($params) {
  ensureLoggedIn();
  $answer = new Answer($params);
  $question = Question::findById($answer->getQuestionId());
  $validator = $answer -> validate();
  if($validator -> hasErrors()){
    redirectRelative("questions/view/$question_id");
  }
  else {
    $answer -> insert();
    $question_id = $question->getId();
    redirectRelative("questions/view/$question_id");
  }
}
?>

