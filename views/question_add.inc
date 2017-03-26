%% views/header.html %%
%% views/errors.html %%
<h1>{{$title}}</h1>
<form action="@@questions/add@@" method="post">
    <label for="title">Title:</label><br>
    <input type="hidden" id="id" name="user_id" value="{{current_user()}}" />
    <input type="text" id="title" name="title" value='{{$question -> getTitle()}}' /><br>
    <label for="content">Content:</label><br>
    <textarea name="content" rows='5' cols='30'>{{$question -> getContent()}}</textarea><br>
    <label for="tags">Tags:</label><br>
    <input type="text" id="tags" name="tags" value='{{$question -> getTags()}}' /><br><br>
    <input type="submit" value="Post" /><br>
</form>
<br>
%% views/footer.html %%
