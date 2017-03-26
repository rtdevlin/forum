<?php
include_once "include/util.inc";
include_once "models/questions.inc";
function get_list($params) {
    $tag = safeParam($params, 0, false);
    $questions = Question::findByTag($tag);
    // @formatter:off
    renderTemplate(
        "views/tags_list.inc",
        array(
            'title' => "Questions tagged '$tag'",
            'questions' => $questions,
        )

    );
    // @formatter:on
}
?>
