%% views/header.html %%
<h1>{{$title}}</h1>
<div class='display'>
    <div class='value'>Posted on: {{$question -> getInsertTs()}} by <a href="@@users/view/{{$question -> getUserId()}}@@">{{$question -> getUser() -> getFirstName()}} {{$question -> getUser() ->  getLastName()}}</a></div><br>
    [[ if($question -> getTags() !== null) : ]]
      <div class='value'>Filed Under: {{$question -> getTags()}}</div><br>
    [[ endif; ]]
    <div class='value'>{{nl2br($question -> getContent())}}</div>
</div>
        [[ if($auth): ]]
          <p>
            <a href="@@questions/delete/{{$question -> getId()}}@@">[Delete]</a>
            <a href="@@questions/edit/{{$question -> getId()}}@@">[Edit]</a>
          </p>
        [[ endif; ]]
<p><a href="@@index@@"><< Back</a></p>
%% views/footer.html %%
