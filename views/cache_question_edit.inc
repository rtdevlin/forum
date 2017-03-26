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
  <li class="right"><a href="/forum/user/view/<?php echo(current_user()); ?>">My profile</a></li>
<?php  else : ?>
  <li class="right"><a href="/forum/login">Log in</a></li>
  <li class="right"><a href="/forum/user/register">Register</a></li>
<?php  endif; ?>
  <li class="right"><a href="/forum/index">Home</a></li>
</ul>
            </div>
            <div style='clear: both;'>

<?php  if (isset($errors)) : ?>
    <p>Please correct the following errors:</p>
    <ul>
<?php    foreach ($errors as $error) : ?>
        <li><?php echo($error); ?></li>
<?php    endforeach; ?>
    </ul>
<?php  endif; ?>
<h1><?php echo($title); ?></h1>
<div class='inputs'>
    <form action="/forum/questions/update" method="post">
        <input type="hidden" id="id" name="id" value="<?php echo($question -> getId()); ?>" />
        <input type="hidden" id="id" name="user_id" value="<?php echo($question -> getUserId()); ?>" />
        <label for="title">Title:</label>
        <input type="text" id="title" name="title" value="<?php echo($question -> getTitle()); ?>" />
        <label for="content">Content:</label>
        <textarea name="content" rows='5' cols='30' ><?php echo($question -> getContent()); ?></textarea><br>
        <label for="tags">Tags:</label>
        <input type="text" id="tags" name="tags" value="<?php echo($question -> getTags()); ?>" /><br><br>
        <input type="submit" value="Save" />
    <form>
</div>
<p><a href="/forum/index"><< Back</a></p>
        <div class="footer">
            Copyright &copy; 2017 Ryan Devlin
        </div>
        </div><!-- content div -->
    </body>
</html>

