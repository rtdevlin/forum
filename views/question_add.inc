%% views/header.html %%
<h1>{{$title}}</h1>
  [[ if(isset($missing_params)) : ]]
    <div class='error'>
      <p>Please fill in the following columns:</p>
      <ul>
      [[ foreach($missing_params as $missing_param) : ]]
        <li>{{$missing_param}}</li>
      [[endforeach;]]
      </ul>
    </div>
  [[endif;]]
<form action="@@questions/add@@" method="post">
    <label for="title">Title:</label><br>
    <input type="text" id="title" name="title" value='{{$question['title']}}' /><br>
    <label for="content">Content:</label><br>
    <textarea name="content" rows='5' cols='30'>{{$question['content']}}</textarea><br>
    <label for="tags">Tags:</label><br>
    <input type="text" id="tags" name="tags" value='{{$question['tags']}}' /><br><br>
    <input type="submit" value="Post" /><br>
</form>
<br>
%% views/footer.html %%
