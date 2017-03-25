%% views/header.html %%
<h1>{{$title}}</h1>
<h2>Recent Questions</h2>
<ol>
    [[ foreach ($questions as $question) : ]]
    <li>
        <a href="@@questions/view/{{$question['id']}}@@">{{$question['title']}}</a><br>
        Posted on: {{substr($question['date'],0,10)}} by <a href="@@users/view/{{$question['user_id']}}@@">{{$question['first_name']}} {{$question['last_name']}}</a><br>
        [[ if(isset($question['tags'])) : ]]
        Filed Under: {{$question['tags']}}<br>
        [[ endif; ]]
        {{substr($question['content'], 0, 100) . '...'}}
    </li>
    [[ endforeach; ]]
</ol>
[[ if (isLoggedIn()) : ]]
  <a href="@@questions/add@@">Add a question</a><br><br>
[[ endif; ]]

%% views/footer.html %%
