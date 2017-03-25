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
<form action="/forum/users/add" method="post">
    <label for="first_name">First name:</label><br>
    <input type="text" id="first_name" name="first_name" value='<?php echo($user['first_name']); ?>' /><br>
    <label for="last_name">Last name:</label><br>
    <input type="text" id="last_name" name="last_name" value='<?php echo($user['last_name']); ?>' /><br>
    <label for="email">E-mail address</label><br>
    <input type="text" id="email" name="email" value='<?php echo($user['email']); ?>' /><br>
    <label for="password">Password</label><br>
    <input type="text" id="password" name="password" value='<?php echo($user['password']); ?>' /><br>
    <input type="submit" value="Save" /><br>
</form>
<br>
        <div class="footer">
            Copyright &copy; 2017 Ryan Devlin
        </div>
        </div><!-- content div -->
    </body>
</html>

