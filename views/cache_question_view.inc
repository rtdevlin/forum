<?php  include_once 'include/util.inc'; ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html>
    <head>
        <title><?php echo($title); ?></title>
        <link rel="stylesheet" href="/forum/static/style.css" />
    </head>
    <body>
        <div class="content">
            <div class='header'>
<ul id="navigation">
<?php  if (isLoggedIn()) : ?>
  <li class="left">Welcome, <?php echo(getName(current_user())); ?></li>
  <li class="right"><a href="/forum/logout">Log out</a></li>
  <li class="right"><a href="/forum/users/view/<?php echo(current_user()); ?>">My profile</a></li>
<?php  else : ?>
  <li class="right"><a href="/forum/login">Log in</a></li>
  <li class="right"><a href="/forum/users/add">Register</a></li>
<?php  endif; ?>
  <li class="right"><a href="/forum/index">Home</a></li>
</ul>
            </div>
            <div style='clear: both;'>

<h1><?php echo($title); ?></h1>
<div class='display'>
    <div class='value'>Posted on: <?php echo($question -> getInsertTs()); ?> by <a href="/forum/users/view/<?php echo($question -> getUserId()); ?>"><?php echo($question -> getUser() -> getFirstName()); ?> <?php echo($question -> getUser() ->  getLastName()); ?></a></div><br>
    <?php  if($tags !== null) : ?>
      <div class='value'>Filed Under: <?php echo(buildTagList($tags)); ?></div><br>
    <?php  endif; ?>
    <div class='value'><?php echo(nl2br($question -> getContent())); ?></div>
</div>
        <?php  if($auth): ?>
          <p>
            <a href="/forum/questions/delete/<?php echo($question -> getId()); ?>">[Delete]</a>
            <a href="/forum/questions/edit/<?php echo($question -> getId()); ?>">[Edit]</a>
          </p>
        <?php  endif; ?>
<?php  if (isLoggedIn()) : ?>
  <form action="/forum/answers/add" method="post">
      <input type="hidden" id="user_id" name="user_id" value="<?php echo(current_user()); ?>" />
      <input type="hidden" id="question_id" name="question_id" value="<?php echo($question->getId()); ?>" />
      <label for="content">Add an asnwer</label><br>
      <textarea name="content" rows='5' cols='60'></textarea><br>
      <input type="submit" value="Submit" /><br>
  </form>
<?php  endif; ?>
<br/>
<h2>Answers</h2>
<ol>
    <?php  foreach ($answers as $answer) : ?>
    <li>
        Posted on: <?php echo(substr($answer -> getInsertTs(),0,10)); ?> by <a href="/forum/users/view/<?php echo($answer -> getUserId()); ?>"><?php echo($answer -> getUser() -> getFirstName()); ?> <?php echo($answer -> getUser() -> getLastName()); ?></a><br>
        <?php echo($answer -> getContent()); ?>
        <?php  if($answer->auth()) : ?>
          <p>
            <a href="/forum/answers/delete/<?php echo($answer -> getId()); ?>">[Delete]</a>
          </p>
        <?php  endif; ?>
    </li>
    <?php  endforeach; ?>
</ol>
<p><a href="/forum/index"><< Back</a></p>
        <div class="footer">
            Copyright &copy; 2017 Ryan Devlin
        </div>
        </div><!-- content div -->
    </body>
</html>

