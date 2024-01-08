
document.addEventListener('DOMContentLoaded', () => {
  const container = document.getElementById('mainContainer');
  const runButton = document.getElementById('runButton');
  const outputDiv = document.getElementById('output');
  const addNewDiscussion = document.getElementById('addNewDiscussion');

  var dialogWindowOpen = false;
  // Backend Post Retrieval 
  runButton.addEventListener('click', async () => {
    try {
      const response = await fetch('/api/hello');
      if (response.ok) {
          const data = await response.text();
          outputDiv.textContent = data;
      } else {
          outputDiv.textContent = 'Error fetching data from the backend.';
      }
    } catch (error) {
      console.error('Error:', error);
      outputDiv.textContent = 'An unexpected error occurred.';
    }
  });



  // For creating new discussions
  addNewDiscussion.addEventListener('click', () => {
    // elem style
    if(dialogWindowOpen)
      return;
    dialogWindowOpen = true;
    const node = document.createElement('div');
    node.style = 'background: grey;';
    node.className = 'box stack-top';

    // Input elem
    const input = document.createElement('input');
    input.type = 'text';
    input.placeholder = 'What are your Ideas?';
    node.appendChild(input);

    // Button elem
    const button = document.createElement('button');
    button.innerText = 'Submit';
    button.addEventListener('click', () => {
      addPost('user', input.value);
      dialogWindowOpen = false;
      node.remove();
    });
    node.appendChild(button);
    // add Node to Container
    container.appendChild(node);
  });
  // who is there


  function addPost(username, postContent){
    const post = document.createElement('div');
    
    post.className = 'post-container';

    const user = document.createElement('p');
    user.innerText = 'Username: ' + username;

    const content = document.createElement('p');
    content.innerText = postContent;

    post.appendChild(user);
    post.appendChild(content);
    container.appendChild(post);
  }
});