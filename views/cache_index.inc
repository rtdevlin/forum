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
  <li class="right"><a href="/forum/user/view/<?php echo(current_user()['user_id']); ?>">My profile</a></li>
<?php  else : ?>
  <li class="right"><a href="/forum/login">Log in</a></li>
  <li class="right"><a href="/forum/user/register">Register</a></li>
<?php  endif; ?>
  <li class="right"><a href="/forum/index">Home</a></li>
</ul>
            </div>
            <div style='clear: both;'>

<h1><?php echo($title); ?></h1>
<h2>Recent Questions</h2>
<ol>
    <?php  foreach ($questions as $question) : ?>
    <li>
        <a href="/forum/questions/view/<?php echo($question['id']); ?>"><?php echo($question['title']); ?></a><br>
        Posted on: <?php echo(substr($question['date'],0,10)); ?> by <a href="/forum/users/view/<?php echo($question['user_id']); ?>"><?php echo($question['first_name']); ?> <?php echo($question['last_name']); ?></a><br>
        <?php  if(isset($question['tags'])) : ?>
        Filed Under: <?php echo($question['tags']); ?><br>
        <?php  endif; ?>
        <?php echo(substr($question['content'], 0, 100) . '...'); ?>
    </li>
    <?php  endforeach; ?>
</ol>
<?php  if (isLoggedIn()) : ?>
  <a href="/forum/questions/add">Add a question</a><br><br>
<?php  endif; ?>

        <div class="footer">
            Copyright &copy; 2017 Ryan Devlin
        </div>
        </div><!-- content div -->
    </body>
</html>

