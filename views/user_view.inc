%% views/header.html %%
<h1>{{$title}}</h1>
<div class='display'>
  <p>First Name: {{$user -> getFirstName()}}
  <p>Last Name: {{$user -> getLastName()}}
  <p>Email: {{$user -> getEmail()}}
  <p>Password: {{preg_replace('/./','*',$user -> getPassword())}}
</div>
        [[ if($auth): ]]
          <p>
            <a href="@@users/delete/{{$user -> getId()}}@@">[Delete]</a>
            <a href="@@users/edit/{{$user -> getId()}}@@">[Edit]</a>
          </p>
        [[ endif; ]]
  <br/>
  <h2>Questions by {{getName($user -> getId())}}</h2>
  <ol>
      [[ foreach ($questions as $question) : ]]
      <li>
          <a href="@@questions/view/{{$question -> getId()}}@@">{{$question -> getTitle()}}</a><br>
          Posted on: {{substr($question -> getInsertTs(),0,10)}} by <a href="@@users/view/{{$question -> getUserId()@@}}">{{$user -> getFirstName()}} {{$user -> getLastName()}}</a><br>
          [[ if($question -> getTags() !== null) : ]]
            Filed Under: {{buildTagList($question -> getTags())}}<br>
          [[ endif; ]]
            {{substr($question -> getContent(), 0, 100) . '...'}}
      </li>
        [[ if($auth): ]]
          <p>
            <a href="@@questions/delete/{{$question -> getId()}}@@">[Delete]</a>
            <a href="@@questions/edit/{{$question -> getId()}}@@">[Edit]</a>
          </p>
        [[ endif; ]]
      [[ endforeach; ]]
  </ol>
%% views/footer.html %%
