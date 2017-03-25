%% views/header.html %%
<h1>{{$title}}</h1>
<div class='display'>
  <p>First Name: {{$user['first_name']}}
  <p>Last Name: {{$user['last_name']}}
  <p>Email: {{$user['email']}}
  <p>Password: {{preg_replace('/./','*',$user['password'])}}
</div>
        [[ if($auth): ]]
          <p>
            <a href="@@users/delete/{{$user[user_id]}}@@">[Delete]</a>
            <a href="@@users/edit/{{$user[user_id]}}@@">[Edit]</a>
          </p>
        [[ endif; ]]
  <br/>
  <h2>Questions by {{getName($user)}}</h2>
  <ol>
      [[ foreach ($questions as $question) : ]]
      <li>
          <a href="@@questions/view/{{$question['id']}}@@">{{$question['title']}}</a><br>
          Posted on: {{substr($question['date'],0,10)}} by <a href="@@users/view/{{$question['user_id']@@}}">{{$user['first_name']}} {{$user['last_name']}}</a><br>
          [[ if(isset($question['tags'])) : ]]
            Filed Under: {{$question['tags']}}<br>
          [[ endif; ]]
            {{substr($question['content'], 0, 100) . '...'}}
      </li>
        [[ if($auth): ]]
          <p>
            <a href="@@questions/delete/{{$question['id']}}@@">[Delete]</a>
            <a href="@@questions/edit/{{$question['id']}}@@">[Edit]</a>
          </p>
        [[ endif; ]]
      [[ endforeach; ]]
  </ol>
%% views/footer.html %%
