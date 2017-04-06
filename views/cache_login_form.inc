<?php  include_once 'include/util.inc'; ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html>
    <head>
        <title><?php echo($title); ?></title>
        <link rel="stylesheet" href="/static/style.css" />
    </head>
    <body>
        <div class="content">
            <div class='header'>
<ul id="navigation">
<?php  if (isLoggedIn()) : ?>
  <li class="left">Welcome, <?php echo(getName(current_user())); ?></li>
  <li class="right"><a href="/logout">Log out</a></li>
  <li class="right"><a href="/users/view/<?php echo(current_user()); ?>">My profile</a></li>
<?php  else : ?>
  <li class="right"><a href="/login">Log in</a></li>
  <li class="right"><a href="/users/add">Register</a></li>
<?php  endif; ?>
  <li class="right"><a href="/index">Home</a></li>
</ul>
            </div>
            <div style='clear: both;'>

<h1><?php echo($title); ?></h1>
<?php  if (isset($errors)) : ?>
    <p>Please correct the following errors:</p>
    <ul>
<?php    foreach ($errors as $error) : ?>
        <li><?php echo($error); ?></li>
<?php    endforeach; ?>
    </ul>
<?php  endif; ?>
<div class='inputs'>
    <form action="/login" method="post">
        <label for="email">Email:</label>
        <input type="text" id="email" name="email" value="<?php echo(isset($email) ? $email : ''); ?>" />
        <label for="password">Password:</label>
        <input type="password" id="password" name="password" value="<?php echo(isset($password) ? $password : ''); ?>" />
        <input type="submit" value="Login" />
    <form>
</div>
<p><a href="/index"><< Back</a></p>
        <div class="footer">
            Copyright &copy; 2017 Ryan Devlin
        </div>
        </div><!-- content div -->
    </body>
</html>

