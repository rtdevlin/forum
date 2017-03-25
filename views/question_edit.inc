%% views/header.html %%
%% views/errors.html %%
<h1>{{$title}}</h1>
<div class='inputs'>
    <form action="@@questions/update@@" method="post">
        <input type="hidden" id="id" name="id" value="{{$question['id']}}" />
        <label for="title">Title:</label>
        <input type="text" id="title" name="title" value="{{$question['title']}}" />
        <label for="content">Content:</label>
        <textarea name="content" rows='5' cols='30' >{{$question['content']}}</textarea><br>
        <label for="tags">Tags:</label>
        <input type="text" id="tags" name="tags" value="{{$question['tags']}}" /><br><br>
        <input type="submit" value="Save" />
    <form>
</div>
<p><a href="@@index@@"><< Back</a></p>
%% views/footer.html %%
