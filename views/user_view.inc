%% views/header.html %%
<h1>{{$title}}</h1>
<div class='display'>
  <p>First Name: {{$user -> getFirstName()}}
  <p>Last Name: {{$user -> getLastName()}}
  <p>Email: {{$user -> getEmail()}}
  <p>Password: {{preg_replace('/./','*',$user -> getPassword())}}
</div>
          <p>
        [[ if($auth || Authenticator::instance() -> can('delete_user')): ]]
            <a href="@@users/delete/{{$user -> getId()}}@@">[Delete]</a>
        [[ endif; ]]
        [[ if($auth || Authenticator::instance() -> can('edit_user')): ]]
            <a href="@@users/edit/{{$user -> getId()}}@@">[Edit]</a>
        [[ endif; ]]
          </p>
  <br/>
  <h2>Questions by {{getName($user -> getId())}}</h2>
    [[ foreach ($questions as $question) : ]]
    <div class='shortquestion'>
        <span class='title'><a href="@@questions/view/{{$question -> getId()}}@@">{{$question -> getTitle()}}</a></span>
        <span class='date'>Posted on: {{substr($question -> getInsertTs(),0,10)}} by <a href="@@users/view/{{$question -> getUserId()}}@@">{{$question -> getUser() -> getFirstName()}} {{$question -> getUser() -> getLastName()}}</a></span>
        [[ if($question -> getTags() !== null) : ]]
        <span class='tags'>Filed Under: {{buildTagList($question -> getTags())}}</span>
        [[ endif; ]]
        [[ if(strlen($question -> getContent()) > 100) : ]]
          <span class='question'>[[echo( formatAsMarkdown(substr($question -> getContent(), 0, 100)."..."))]]</span>
        [[ else : ]]
          <span class='question'>[[echo( formatAsMarkdown($question -> getContent()) )]]</span>
        [[ endif; ]]
        [[ if($auth): ]]
          <p>
            <a href="@@questions/delete/{{$question -> getId()}}@@">[Delete]</a>
            <a href="@@questions/edit/{{$question -> getId()}}@@">[Edit]</a>
          </p>
        [[ endif; ]]
    </div>
    [[ endforeach; ]]
%% views/footer.html %%
