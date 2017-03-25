<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html>
    <head>
        <title><?php echo($title); ?></title>
        <link rel="stylesheet" href="/forum/static/style.css" />
<style>
  a.nav { float: right; margin: 3px;}
</style>
    </head>
    <body>
        <div class="content">

<?php  include_once 'include/util.inc'; ?>
<?php  if (isLoggedIn()) : ?>
  Welcome, <?php echo(getName(current_user())); ?>
    <a class='nav' href='/forum/logout'>Log Out</a>
    <a class='nav' href="/forum/users/view/<?php echo(current_user()['user_id']); ?>">My Profile</a>
<?php  else : ?>
    <a class='nav' href='/forum/login'>Log in</a>
    <a class='nav' href='/forum/users/add'>Register</a>
<?php  endif; ?>
    <a class='nav' href='/forum/index'>Home</a>

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

