%% views/header.html %%
%% views/errors.html %%
<h1>{{$title}}</h1>
<form action="@@users/add@@" method="post">
    <label for="first_name">First name:</label><br>
    <input type="text" id="first_name" name="first_name" value='{{$user['first_name']}}' /><br>
    <label for="last_name">Last name:</label><br>
    <input type="text" id="last_name" name="last_name" value='{{$user['last_name']}}' /><br>
    <label for="email">E-mail address</label><br>
    <input type="text" id="email" name="email" value='{{$user['email']}}' /><br>
    <label for="password">Password</label><br>
    <input type="text" id="password" name="password" value='{{$user['password']}}' /><br>
    <input type="submit" value="Save" /><br>
</form>
<br>
%% views/footer.html %%
