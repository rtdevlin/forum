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
  <p>First Name: <?php echo($user -> getFirstName()); ?>
  <p>Last Name: <?php echo($user -> getLastName()); ?>
  <p>Email: <?php echo($user -> getEmail()); ?>
  <p>Password: <?php echo(preg_replace('/./','*',$user -> getPassword())); ?>
</div>
        <?php  if($auth): ?>
          <p>
            <a href="/forum/users/delete/<?php echo($user -> getId()); ?>">[Delete]</a>
            <a href="/forum/users/edit/<?php echo($user -> getId()); ?>">[Edit]</a>
          </p>
        <?php  endif; ?>
  <br/>
  <h2>Questions by <?php echo(getName($user -> getId())); ?></h2>
  <ol>
      <?php  foreach ($questions as $question) : ?>
      <li>
          <a href="/forum/questions/view/<?php echo($question -> getId()); ?>"><?php echo($question -> getTitle()); ?></a><br>
          Posted on: <?php echo(substr($question -> getInsertTs(),0,10)); ?> by <a href="/forum/users/view/<?php echo($question -> getUserId()); ?>"><?php echo($user -> getFirstName()); ?> <?php echo($user -> getLastName()); ?></a><br>
          <?php  if($question -> getTags() !== null) : ?>
            Filed Under: <?php echo(buildTagList($question -> getTags())); ?><br>
          <?php  endif; ?>
            <?php echo(substr($question -> getContent(), 0, 100) . '...'); ?>
      </li>
        <?php  if($auth): ?>
          <p>
            <a href="/forum/questions/delete/<?php echo($question -> getId()); ?>">[Delete]</a>
            <a href="/forum/questions/edit/<?php echo($question -> getId()); ?>">[Edit]</a>
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

