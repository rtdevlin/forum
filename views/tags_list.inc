%% views/header.html %%
<h1>{{$title}}</h1>
<ol>
    [[ foreach ($questions as $question) : ]]
    <li>
        <a href="@@questions/view/{{$question -> getId()}}@@">{{$question -> getTitle()}}</a><br>
        Posted on: {{substr($question -> getInsertTs(),0,10)}} by <a href="@@users/view/{{$question -> getUserId()}}@@">{{$question -> getUser() -> getFirstName()}} {{$question -> getUser() -> getLastName()}}</a><br>
        [[ if($question -> getTags() !== null) : ]]
        Filed Under: {{buildTagList($question -> getTags())}}<br>
        [[ endif; ]]
        [[ if(strlen($question -> getContent()) > 100) : ]]
          <span class='question'>[[echo( formatAsMarkdown(substr($question -> getContent(), 0, 100)."..."))]]</span>
        [[ else : ]]
          <span class='question'>[[echo( formatAsMarkdown($question -> getContent()) )]]</span>
        [[ endif; ]]
    </li>
    [[ endforeach; ]]
</ol>
[[ if (isLoggedIn()) : ]]
  <a href="@@questions/add@@">Add a question</a><br><br>
[[ endif; ]]

%% views/footer.html %%
