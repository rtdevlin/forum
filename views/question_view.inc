%% views/header.html %%
<h1>{{$title}}</h1>
<div class='display'>
    <div class='value'>Posted on: {{$question['date']}} by <a href="@@users/view/{{$question['user_id']}}@@">{{$question['first_name']}} {{$question['last_name']}}</a></div><br>
    [[ if(isset($question['tags'])) : ]]
      <div class='value'>Filed Under: {{$question['tags']}}</div><br>
    [[ endif; ]]
    <div class='value'>{{nl2br($question['content'])}}</div>
</div>
        [[ if($auth): ]]
          <p>
            <a href="@@questions/delete/{{$question['id']}}@@">[Delete]</a>
            <a href="@@questions/edit/{{$question['id']}}@@">[Edit]</a>
          </p>
        [[ endif; ]]
<p><a href="@@index@@"><< Back</a></p>
%% views/footer.html %%
