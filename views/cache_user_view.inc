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
<div class='display'>
  <p>First Name: <?php echo($user['first_name']); ?>
  <p>Last Name: <?php echo($user['last_name']); ?>
  <p>Email: <?php echo($user['email']); ?>
  <p>Password: <?php echo(preg_replace('/./','*',$user['password'])); ?>
</div>
        <?php  if($auth): ?>
          <p>
            <a href="/forum/users/delete/<?php echo($user[user_id]); ?>">[Delete]</a>
            <a href="/forum/users/edit/<?php echo($user[user_id]); ?>">[Edit]</a>
          </p>
        <?php  endif; ?>
  <br/>
  <h2>Questions by <?php echo(getName($user)); ?></h2>
  <ol>
      <?php  foreach ($questions as $question) : ?>
      <li>
          <a href="/forum/questions/view/<?php echo($question['id']); ?>"><?php echo($question['title']); ?></a><br>
          Posted on: <?php echo(substr($question['date'],0,10)); ?> by <a href="/forum/users/view/<?php echo($question['user_id']); ?>"><?php echo($user['first_name']); ?> <?php echo($user['last_name']); ?></a><br>
          <?php  if(isset($question['tags'])) : ?>
            Filed Under: <?php echo($question['tags']); ?><br>
          <?php  endif; ?>
            <?php echo(substr($question['content'], 0, 100) . '...'); ?>
      </li>
        <?php  if($auth): ?>
          <p>
            <a href="/forum/questions/delete/<?php echo($question['id']); ?>">[Delete]</a>
            <a href="/forum/questions/edit/<?php echo($question['id']); ?>">[Edit]</a>
          </p>
        <?php  endif; ?>
      <?php  endforeach; ?>
  </ol>
        <div class="footer">
            Copyright &copy; 2017 Ryan Devlin
        </div>
        </div><!-- content div -->
    </body>
</html>

