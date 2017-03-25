%% views/header.html %%
%% views/errors.html %%
<h1>{{$title}}</h1>
<div class='inputs'>
    <form action="@@users/update@@" method="post">
        <input type="hidden" id="user_id" name="user_id" value="{{$user['user_id']}}" />
        <label for="title">First Name:</label>
        <input type="text" id="first_name" name="first_name" value="{{$user['first_name']}}" />
        <label for="content">Last Name:</label>
        <input type="text" id="last_name" name="last_name" value="{{$user['last_name']}}" />
        <label for="content">Email:</label>
        <input type="text" id="email" name="email" value="{{$user['email']}}" />
        <label for="content">Password:</label>
        <input type="password" id="password" name="password" value="{{$user['password']}}" /><br><br>
        <input type="submit" value="Save" />
    <form>
</div>
<p><a href="@@index@@"><< Back</a></p>
%% views/footer.html %%
