%% views/header.html %%
%% views/errors.html %%
<h1>{{$title}}</h1>
<div class='inputs'>
    <form action="@@questions/update@@" method="post">
        <input type="hidden" id="id" name="id" value="{{$question -> getId()}}" />
        <input type="hidden" id="id" name="user_id" value="{{$question -> getUserId()}}" />
        <label for="title">Title:</label>
        <input type="text" id="title" name="title" value="{{$question -> getTitle()}}" />
        <label for="content">Content:</label>
        <textarea name="content" rows='5' cols='30' >{{$question -> getContent()}}</textarea><br>
        <label for="tags">Tags:</label>
        <input type="text" id="tags" name="tags" value="{{$question -> getTags()}}" /><br><br>
        <input type="submit" value="Save" />
    <form>
</div>
<p><a href="@@index@@"><< Back</a></p>
%% views/footer.html %%
