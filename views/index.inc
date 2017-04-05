%% views/header.html %%
<h1>{{$title}}</h1>
<h2>Recent Questions</h2>
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
    </div>
    [[ endforeach; ]]
[[ if (isLoggedIn()) : ]]
  <a href="@@questions/add@@">Add a question</a>
[[ endif; ]]

%% views/footer.html %%
