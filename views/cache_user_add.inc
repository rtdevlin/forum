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
    <input type="text" id="first_name" name="first_name" value='<?php echo($user -> getFirstName()); ?>' /><br>
    <label for="last_name">Last name:</label><br>
    <input type="text" id="last_name" name="last_name" value='<?php echo($user -> getLastName()); ?>' /><br>
    <label for="email">E-mail address</label><br>
    <input type="text" id="email" name="email" value='<?php echo($user -> getEmail()); ?>' /><br>
    <label for="password">Password</label><br>
    <input type="password" id="password" name="password" value='<?php echo($user -> getPassword()); ?>' /><br>
    <input type="submit" value="Save" /><br>
</form>
<br>
        <div class="footer">
            Copyright &copy; 2017 Ryan Devlin
        </div>
        </div><!-- content div -->
    </body>
</html>

