%% views/header.html %%
%% views/errors.html %%
<h1>{{$title}}</h1>
<div class='inputs'>
    <form action="@@users/update@@" method="post">
        <input type="hidden" id="id" name="id" value="{{$user -> getId()}}" />
        <input type="hidden" id="email" name="email" value="{{$user -> getEmail()}}" />
        <label for="title">First Name:</label>
        <input type="text" id="first_name" name="first_name" value="{{$user -> getFirstName()}}" />
        <label for="content">Last Name:</label>
        <input type="text" id="last_name" name="last_name" value="{{$user -> getLastName()}}" />
        <span>Email:</span><br />
        <span>{{$user -> getEmail()}}</span>
        <label for="content">Password:</label>
        <input type="password" id="password" name="password" value="{{$user -> getPassword()}}" /><br><br>
        <input type="submit" value="Save" />
    <form>
</div>
<p><a href="@@index@@"><< Back</a></p>
%% views/footer.html %%
