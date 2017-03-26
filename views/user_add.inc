%% views/header.html %%
%% views/errors.html %%
<h1>{{$title}}</h1>
<form action="@@users/add@@" method="post">
    <label for="first_name">First name:</label><br>
    <input type="text" id="first_name" name="first_name" value='{{$user -> getFirstName()}}' /><br>
    <label for="last_name">Last name:</label><br>
    <input type="text" id="last_name" name="last_name" value='{{$user -> getLastName()}}' /><br>
    <label for="email">E-mail address</label><br>
    <input type="text" id="email" name="email" value='{{$user -> getEmail()}}' /><br>
    <label for="password">Password</label><br>
    <input type="password" id="password" name="password" value='{{$user -> getPassword()}}' /><br>
    <input type="submit" value="Save" /><br>
</form>
<br>
%% views/footer.html %%
