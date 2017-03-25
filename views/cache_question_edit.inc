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
        <input type="hidden" id="id" name="id" value="<?php echo($question['id']); ?>" />
        <label for="title">Title:</label>
        <input type="text" id="title" name="title" value="<?php echo($question['title']); ?>" />
        <label for="content">Content:</label>
        <textarea name="content" rows='5' cols='30' ><?php echo($question['content']); ?></textarea><br>
        <label for="tags">Tags:</label>
        <input type="text" id="tags" name="tags" value="<?php echo($question['tags']); ?>" /><br><br>
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

