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
    <div class='value'>Posted on: <?php echo($question['date']); ?> by <a href="/forum/users/view/<?php echo($question['user_id']); ?>"><?php echo($question['first_name']); ?> <?php echo($question['last_name']); ?></a></div><br>
    <?php  if(isset($question['tags'])) : ?>
      <div class='value'>Filed Under: <?php echo($question['tags']); ?></div><br>
    <?php  endif; ?>
    <div class='value'><?php echo(nl2br($question['content'])); ?></div>
</div>
        <?php  if($auth): ?>
          <p>
            <a href="/forum/questions/delete/<?php echo($question['id']); ?>">[Delete]</a>
            <a href="/forum/questions/edit/<?php echo($question['id']); ?>">[Edit]</a>
          </p>
        <?php  endif; ?>
<p><a href="/forum/index"><< Back</a></p>
        <div class="footer">
            Copyright &copy; 2017 Ryan Devlin
        </div>
        </div><!-- content div -->
    </body>
</html>

