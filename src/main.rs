use std::env::VarError;

use octocrab::Octocrab;

#[tokio::main]
async fn main() -> octocrab::Result<()> {
    let token = std::env::var("GITHUB_TOKEN");
    let errorMsg = "Please set the GITHUB_TOKEN environment variable to your github token before using";

    let token = match token {
        Ok(T) => T,
        Err(_) => errorMsg.to_string(),
    };

    if token == errorMsg {
        println!("{}", errorMsg);
        std::process::exit(1);
    }

    let octocrab = Octocrab::builder().personal_token(token.to_string()).build()?;

    let orgs = octocrab.orgs("uvmcs120s2022").list_repos().send().await?;

    println!("{:?}", orgs);

    Ok(())
}