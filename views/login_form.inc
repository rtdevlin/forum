%% views/header.html %%
<h1>{{$title}}</h1>
%% views/errors.html %%
<div class='inputs'>
    <form action="@@login@@" method="post">
        <label for="email">Email:</label>
        <input type="text" id="email" name="email" value="{{isset($email) ? $email : ''}}" />
        <label for="password">Password:</label>
        <input type="password" id="password" name="password" value="{{isset($password) ? $password : ''}}" />
        <input type="submit" value="Login" />
    <form>
</div>
<p><a href="@@index@@"><< Back</a></p>
%% views/footer.html %%
