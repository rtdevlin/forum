%% views/header.html %%
<h1>{{$title}}</h1>
<div class='display'>
    <div class='value'>Posted on: {{$question -> getInsertTs()}} by <a href="@@users/view/{{$question -> getUserId()}}@@">{{$question -> getUser() -> getFirstName()}} {{$question -> getUser() ->  getLastName()}}</a></div><br>
    [[ if($tags !== null) : ]]
      <div class='value'>Filed Under: {{buildTagList($tags)}}</div><br>
    [[ endif; ]]
    <div class='value'>{{nl2br($question -> getContent())}}</div>
</div>
        [[ if($auth): ]]
          <p>
            <a href="@@questions/delete/{{$question -> getId()}}@@">[Delete]</a>
            <a href="@@questions/edit/{{$question -> getId()}}@@">[Edit]</a>
          </p>
        [[ endif; ]]
[[ if (isLoggedIn()) : ]]
  <form action="@@answers/add@@" method="post">
      <input type="hidden" id="user_id" name="user_id" value="{{current_user()}}" />
      <input type="hidden" id="question_id" name="question_id" value="{{$question->getId()}}" />
      <label for="content">Add an asnwer</label><br>
      <textarea name="content" rows='5' cols='60'></textarea><br>
      <input type="submit" value="Submit" /><br>
  </form>
[[ endif; ]]
<br/>
<h2>Answers</h2>
<ol>
    [[ foreach ($answers as $answer) : ]]
    <li>
        Posted on: {{substr($answer -> getInsertTs(),0,10)}} by <a href="@@users/view/{{$answer -> getUserId()}}@@">{{$answer -> getUser() -> getFirstName()}} {{$answer -> getUser() -> getLastName()}}</a><br>
        {{$answer -> getContent()}}
        [[ if($answer->auth()) : ]]
          <p>
            <a href="@@questions/delete/{{$answer -> getId()}}@@">[Delete]</a>
          </p>
        [[ endif; ]]
    </li>
    [[ endforeach; ]]
</ol>
<p><a href="@@index@@"><< Back</a></p>
%% views/footer.html %%
