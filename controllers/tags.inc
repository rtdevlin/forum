<?php
include_once "include/util.inc";
include_once "models/questions.inc";
include_once "models/question_tags.inc";
include_once "models/tag.inc";
function get_list($params) {
    $tag_name = safeParam($params, 0, false);
    $tag = Tag::findByName($tag_name);
    $bridge_rows = QuestionTag::findByTagId($tag -> getId());
    $question_ids = array();
    foreach($bridge_rows as $row){
      $question_ids[] = $row -> getQuestionId();
    }
    $questions = Question::findByIds($question_ids);
    // @formatter:off
    renderTemplate(
        "views/tags_list.inc",
        array(
            'title' => "Questions tagged '$tag_name'",
            'questions' => $questions,
        )

    );
    // @formatter:on
}
?>
